import sys

# Update UserSettings.h
with open('src/UserSettings.h', 'r') as f:
    user_settings = f.read()

if 'WAIT_TOLERANCE_KEY' not in user_settings:
    user_settings = user_settings.replace(
        '#define SCROLL_SPEED_KEY "scroll-speed"',
        '#define SCROLL_SPEED_KEY "scroll-speed"\n#define WAIT_TOLERANCE_KEY "wait-tolerance"'
    )
    with open('src/UserSettings.h', 'w') as f:
        f.write(user_settings)

# Update gschema.xml
with open('extra/com.github.linthesia.linthesia.gschema.xml', 'r') as f:
    gschema = f.read()

if 'wait-tolerance' not in gschema:
    gschema = gschema.replace(
        '    <key name="scroll-speed" type="s">\n      <default>"3250000"</default>\n    </key>',
        '    <key name="scroll-speed" type="s">\n      <default>"3250000"</default>\n    </key>\n\n    <key name="wait-tolerance" type="s">\n      <default>"500000"</default>\n    </key>'
    )
    with open('extra/com.github.linthesia.linthesia.gschema.xml', 'w') as f:
        f.write(gschema)

print("wait_mode_patch done.")
