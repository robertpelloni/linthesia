// -*- mode: c++; coding: utf-8 -*-

// Linthesia

// Copyright (c) 2007 Nicholas Piegdon
// Adaptation to GNU/Linux by Oscar Aceña
// See COPYING for license information

#include <string>
#include <locale>
#include <libintl.h>
#include <pangomm/init.h>
#include <pangomm.h>

#include "OSGraphics.h"
#include "StringUtil.h"
#include "FileSelector.h"
#include "UserSettings.h"
#include "Version.h"
#include "CompatibleSystem.h"
#include "LinthesiaError.h"
#include "Tga.h"
#include "Renderer.h"
#include "SharedState.h"
#include "GameState.h"
#include "TitleState.h"
#include "DpmsThread.h"
#include "SongLibState.h"

#include "libmidi/Midi.h"
#include "libmidi/MidiUtil.h"

#include "MainWindow.h"
#include "InputManager.h"

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/stat.h>

#include <iostream>
#include <libgen.h>

#include <SDL2/SDL_image.h>

#define _(String) gettext (String)

using namespace std;

GameStateManager* state_manager;
bool main_loop_running = true;

char *sqlite_db_str;
sqlite3 *db;

const static string friendly_app_name = STRING("Linthesia " <<
                                               LinthesiaVersionString);

const static string error_header1 = _("Linthesia detected a");
const static string error_header2 = _(" problem and must close:\n\n");
const static string error_footer = _("\n\nIf you don't think this should have "
  "happened, please fill a bug report on : \nhttps://github.com/linthesia/linthesia\n\nThank you.");

const static int vsync_interval = 1;

char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string & option)
{
    return std::find(begin, end, option) != end;
}

std::string getExePath()
// https://stackoverflow.com/questions/23943239/how-to-get-path-to-current-exe-file-on-linux
{
  char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
  return std::string( dirname(result), (count > 0) ? count : 0 );
}

void print_version() {
  cout << friendly_app_name << endl;
}

void show_help() {
  print_version();
  cout << endl << _("Options: ") << endl << endl
     << "\t" << "-f" << " " << _("to load files") << endl
     << "\t" << "-w" << " " << _("to start in window mode") << endl
     << "\t" << "-W" << " " << _("to start full screem") << endl
     << "\t" << "--min-key" << " " << _("to define min key") << endl
     << "\t" << "--max-key" << " " << _("to define max key") << endl
     << "\t" << "--lib-path" << " " << _("to define directory for music library") << endl
     << "\t" << "--reset-lib-path" << " " << _("reset directory for music library to "MUSICDIR) << endl
     << "\t" << "--help" << " " << _("show this help") << endl
     << "\t" << "--version" << " " << _("show linthesia version") << endl
     << endl;
}

bool has_invalid_options(int argc, char *argv[]) {
  for (char **pargv = argv; *pargv != NULL; pargv++) {
    char i = *pargv[0];
    char* j = *pargv+1;
    if ((i == '-') && (strcmp(j, "f") != 0 &&
                       strcmp(j, "w") != 0 &&
                       strcmp(j, "W") != 0 &&
                       strcmp(j, "-min-key") != 0 &&
                       strcmp(j, "-max-key") != 0 &&
                       strcmp(j, "-help") != 0 &&
                       strcmp(j, "-lib-path") != 0 &&
                       strcmp(j, "-reset-lib-path") != 0 &&
                       strcmp(j, "-version") != 0)) {
      cout << _("Invalid option: ") << *pargv << endl << endl;
      return true;
    }
  }
  return false;
}

int main(int argc, char *argv[]) {
  setlocale (LC_ALL, "");
  textdomain("linthesia");

  try {

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
      throw LinthesiaSDLError(_("error initializing SDL"));

    Pango::init();

    string file_opt("");

    UserSetting::Initialize();

    int show_help_exit_status = 0;
    bool invalid_options = has_invalid_options(argc, argv);
    if (invalid_options) {
      show_help_exit_status = 1;
    }

    if (invalid_options || cmdOptionExists(argv, argv+argc, "--help")) {
      show_help();
      return show_help_exit_status;
    }

    if (cmdOptionExists(argv, argv+argc, "--version")) {
      print_version();
      return 0;
    }

    if (cmdOptionExists(argv, argv+argc, "-f"))
      file_opt = string(getCmdOption(argv, argv + argc, "-f"));

    bool windowed = cmdOptionExists(argv, argv+argc, "-w");
    bool fullscreen = cmdOptionExists(argv, argv+argc, "-W");
    bool headless = cmdOptionExists(argv, argv+argc, "--headless");
    if (cmdOptionExists(argv, argv+argc, "--lib-path")) {
      string path(getCmdOption(argv, argv + argc, "--lib-path"));
      UserSetting::Set(SONG_LIB_PATH_KEY, path);
      UserSetting::Set(SONG_LIB_DIR_SETTINGS_KEY, path);
    }
    if (cmdOptionExists(argv, argv+argc, "--reset-lib-path")) {
      UserSetting::Set(SONG_LIB_PATH_KEY, MUSICDIR);
      UserSetting::Set(SONG_LIB_DIR_SETTINGS_KEY, MUSICDIR);
    }

    // strip any leading or trailing quotes from the filename
    // argument (to match the format returned by the open-file
    // dialog later).
    if (file_opt.length() > 0 &&
        file_opt[0] == '\"')
      file_opt = file_opt.substr(1, file_opt.length() - 1);

    if (file_opt.length() > 0 &&
        file_opt[file_opt.length()-1] == '\"')
      file_opt = file_opt.substr(0, file_opt.length() - 1);
    
    Midi *midi = 0;

    // attempt to open the midi file given on the command line first
    if (file_opt != "") {
      try {
        midi = new Midi(Midi::ReadFromFile(file_opt));
      }

      catch (const MidiError &e) {
        string wrapped_description = STRING(_("Problem while loading file: ") <<
                                            file_opt <<
                                            "\n") + e.GetErrorDescription();
        Compatible::ShowError(wrapped_description);

        file_opt = "";
        midi = 0;
      }
    }

    /* Loading the Sqlite Library
    */
    string tmp_user_db_str = UserSetting::Get(SQLITE_DB_KEY, "");

    if (tmp_user_db_str.empty() ) {
      struct stat st;

      // no user pref : let's create one !
      struct passwd *pw = getpwuid(getuid());
      sqlite_db_str = strcat(pw->pw_dir, "/.local/linthesia");
      if ( stat(sqlite_db_str, &st) == -1) {
        const int dir_err = mkdir(sqlite_db_str, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (-1 == dir_err)
        {
          fprintf(stderr, _("Error creating directory : %s\n"), sqlite_db_str);
          exit(1);
        }
      }
      sqlite_db_str = strcat(sqlite_db_str, "/music.sqlite");
      UserSetting::Set(SQLITE_DB_KEY, sqlite_db_str);
    } else {
        // user pref exist : let's use it !
        sqlite_db_str = (char*) tmp_user_db_str.c_str();
    }

    if (sqlite3_open(sqlite_db_str, &db)) {
      fprintf(stderr, _("Can't open database: %s\n"), sqlite3_errmsg(db));
      return(0);
    } else {
      // fprintf(stderr, _("Opened database successfully\n"));
      sqlite3_close(db);
    }

    const int default_sw = 1280;
    const int default_sh = 720;
    Uint32 flags = SDL_WINDOW_OPENGL;

    // Lauch fullscreen if asked for it OR if neither fullllscreen and windowed is asked AND we are not in jail.
    bool injail = true; // FIXME : how to detect we are injail without doing something nasty ?
                        // Jail is launched by AppImage, within :
                        //   firejail --quiet --noprofile --net=none --appimage ./"$FILENAME" &

    if (fullscreen || ( (!windowed && !fullscreen) && (!injail ) ) ) {
      flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    } else
    {
      flags |= SDL_WINDOW_RESIZABLE;
    }

    if (!headless) {
      state_manager = new GameStateManager(default_sw, default_sh);
      chdir (getExePath().c_str());
    } else {
      // Headless initialization
      state_manager = new GameStateManager(default_sw, default_sh);
      chdir(getExePath().c_str());
    }

    // Init DHMS thread once for the whole program
    DpmsThread* dpms_thread = new DpmsThread();

    // do this after gl context is created (ie. after da realized)
    SharedState state;
    state.dpms_thread = dpms_thread;
    if (midi) {
      state.song_title = FileSelector::TrimFilename(file_opt);
      state.midi = midi;
      state_manager->SetInitialState(new TitleState(state));
    }
    else {
      // if midi couldn't be opened from command line filename or there
      // simply was no command line filename, use a song-lib.
      state_manager->SetInitialState(new SongLibState(state));
    }

    // get refresh rate from user settings
    int default_rate = 300;

    string user_rate = UserSetting::Get(REFRESH_RATE_KEY, "");

    if (user_rate.empty()) {
      user_rate = STRING(default_rate);
      UserSetting::Set(REFRESH_RATE_KEY, user_rate);
    }
    else {
      istringstream iss(user_rate);
      if (not (iss >> default_rate)) {
        Compatible::ShowError(_("Invalid setting for 'refresh_rate' key.\n\nReset to default value when reload."));
        UserSetting::Set(REFRESH_RATE_KEY, "");
      }
    }

    UserSetting::Set(MIN_KEY_KEY, "");
    UserSetting::Set(MAX_KEY_KEY, "");

    if (cmdOptionExists(argv, argv+argc, "--min-key")) {
      string min_key = STRING(getCmdOption(argv, argv + argc, "--min-key"));
      UserSetting::Set(MIN_KEY_KEY, min_key);
    }

    if (cmdOptionExists(argv, argv+argc, "--max-key")) {
      string max_key = STRING(getCmdOption(argv, argv + argc, "--max-key"));
      UserSetting::Set(MAX_KEY_KEY, max_key);
    }

    auto app = Gtk::Application::create("com.github.linthesia.linthesia");

    if (!headless) {
      InputManager input_manager(state_manager);
      MainWindow window(state_manager, &input_manager);

      app->run(window);

      midiStop();
      delete dpms_thread;
      SDL_Quit();
    } else {
      // Headless loop using GTKmm signals
      sigc::connection timeout_connection = Glib::signal_timeout().connect([&]() {
        SDL_Event Event;
        while (SDL_PollEvent(&Event)) {
          if (Event.type == SDL_QUIT) {
            main_loop_running = false;
            app->quit();
          }
        }
        state_manager->Update(false);
        return main_loop_running;
      }, 16);

      app->hold();
      app->run();

      midiStop();
      delete dpms_thread;
      SDL_Quit();
    }

    return 0;
  }
  catch (const LinthesiaError &e) {
    string wrapped_description = STRING(error_header1 <<
                                        error_header2 <<
                                        e.GetErrorDescription() <<
                                        error_footer);
    Compatible::ShowError(wrapped_description);
  }

  catch (const MidiError &e) {
    string wrapped_description = STRING(error_header1 <<
                                        " MIDI" <<
                                        error_header2 <<
                                        e.GetErrorDescription() <<
                                        error_footer);
    Compatible::ShowError(wrapped_description);
  }
  catch (const exception &e) {
    string wrapped_description = STRING(_("Linthesia detected an unknown "
                                        "problem and must close!  '") <<
                                        e.what() << "'" << error_footer);
    Compatible::ShowError(wrapped_description);
  }

  catch (...) {
    string wrapped_description = STRING(_("Linthesia detected an unknown "
                                        "problem and must close!") <<
                                        error_footer);
    Compatible::ShowError(wrapped_description);
  }

  return 1;
}

