# Alacritty Theme Selector

* TUI theme selector for alacritty and similar programs written purely in C using the ncurses library
* Utilizes vim bindings for menu navigation

## Setup

### Importing Themes
* Either manually put theme files (.toml) in the `~/.config/alacritty/` directory or clone existing themes like the following:

```
git clone https://github.com/alacritty/alacritty-theme
mv alacritty-theme/themes/* ~/.config/alacritty/
rm -rf alacritty-theme/
```

### Building the binary

```
git clone https://github.com/aditya23043/AlacSel
cd AlacSel/
make
```

## Run

* Either run in the `AlacSel/` directory with `make run`
* Or copy the `AlacSel/bin/main` binary to another path and run the executable

## Configuration

* Edit the defines inside `AlacSel/src/main.h` to tweak the alacritty configuration file path and directory
