import re

with open('src/PlayingState.h', 'r') as f:
    ps_h = f.read()

if 'm_wait_grace_timer' not in ps_h:
    ps_h = ps_h.replace(
        '  microseconds_t m_lead_out;',
        '  microseconds_t m_lead_out;\n  microseconds_t m_wait_grace_timer;\n  microseconds_t m_wait_tolerance;'
    )
    with open('src/PlayingState.h', 'w') as f:
        f.write(ps_h)

with open('src/PlayingState.cpp', 'r') as f:
    ps_cpp = f.read()

if 'm_wait_tolerance = ' not in ps_cpp:
    ps_cpp = ps_cpp.replace(
        'm_lead_out = String::ToMicroseconds(UserSetting::Get(LEAD_OUT_TIME_KEY, "1000000"));',
        'm_lead_out = String::ToMicroseconds(UserSetting::Get(LEAD_OUT_TIME_KEY, "1000000"));\n  m_wait_tolerance = String::ToMicroseconds(UserSetting::Get(WAIT_TOLERANCE_KEY, "500000"));\n  m_wait_grace_timer = 0;'
    )

    ps_cpp = ps_cpp.replace(
        'm_lead_out(1000000),',
        'm_lead_out(1000000),\n  m_wait_grace_timer(0),\n  m_wait_tolerance(500000),'
    )

    # In Update(), we need to handle grace period for waiting
    # We find where areAllRequiredKeysPressed() is checked
    # There's a section:
    #     if (!areAllRequiredKeysPressed() && m_state.song->IsLearning(track_id)) {
    # We need to implement grace period

    with open('src/PlayingState.cpp', 'w') as f:
        f.write(ps_cpp)

print("fix_playingstate_waitmode.py done.")
