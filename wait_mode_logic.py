import re

with open('src/PlayingState.cpp', 'r') as f:
    ps_cpp = f.read()

# Replace the update logic to incorporate m_wait_grace_timer
update_logic_old = """    if (areAllRequiredKeysPressed())
    {
      Play(delta_microseconds);
//    m_should_wait_after_retry = false; // always reset onces pressed
    }
    else
    {
      m_current_combo = 0;
      m_add_score = false;
    }"""

update_logic_new = """    if (areAllRequiredKeysPressed())
    {
      Play(delta_microseconds);
      m_wait_grace_timer = 0; // Reset grace timer when keys are pressed
//    m_should_wait_after_retry = false; // always reset onces pressed
    }
    else
    {
      if (m_wait_grace_timer < m_wait_tolerance) {
        // Still within grace period, continue playing normally
        m_wait_grace_timer += delta_microseconds;
        Play(delta_microseconds);
      } else {
        // Grace period expired, stop and wait
        m_current_combo = 0;
        m_add_score = false;
      }
    }"""

if update_logic_old in ps_cpp:
    ps_cpp = ps_cpp.replace(update_logic_old, update_logic_new)
    print("Replaced update logic.")
else:
    print("Could not find update logic old!")

with open('src/PlayingState.cpp', 'w') as f:
    f.write(ps_cpp)
