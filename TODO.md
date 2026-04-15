# TODO

- [ ] Implement the Scoring System (Perfect, Good, Miss) and Streak popups as mentioned in the ROADMAP and MEMORY. Ensure hits are visualized correctly (Early vs Late).
- [ ] Polish "Wait Mode" (Learning mode) grace period logic (`WAIT_TOLERANCE_KEY`).
- [ ] Implement "Sight Reading" (Standard notation view/SheetMusicDisplay) toggled via F7 to procedurally render beams, stems, and key signatures.
- [ ] Improve UI/UX with tooltips and more extensive documentation across the user interface.
- [ ] Refactoring: Ensure `Renderer` transition from SDL to GTKmm is completed seamlessly. Currently, `Renderer` is instantiated with an empty `GLContext` and `PGContext` in `main.cpp` just to pass compilation.
