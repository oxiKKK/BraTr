# v0.1.5
 ## Bugfixes
- Fixed bug where upon closing the file opening dialog, the program would crash.
- Fixed bugs with reading non-existing files (e.g. files that were opened and then renamed/removed)
- Fixed crash upon opening non-existent previously opened file.

# v0.1.4
## App
- Tweaked the size of braille letter dots.

# v0.1.3
## Bugfixes
- Fixed bug where the program icon didn't work.

# v0.1.2
## App
- Got rid of the option to open previously opened file.
- Fixed a bug where the invalid character marker wasn't rendering correctly.
- Changed the ratio of letter rectangles to 3/4. This is customizable and can be changed to whatever ratio.

# v0.1.1
## Source code
- Added missing glfw.lib file.
- Added "misc" folder to the solution tree.
- Added new CPlatform class
- Changed scale of dots when rendering braille letters
- Applied the scrollbar width to the maximum width of the translation side

## App
- Made dot invards shift a little bit bigger

## Bugfixes
- Fixed bug when where there weren't any previously opened files saved, the program would crash.
- Made it so that letters no longer clip through the vertical scrollbar when rendered.