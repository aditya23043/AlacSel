<img width="3420" height="2137" alt="Screenshot 2025-12-19 at 11 40 33 AM" src="https://github.com/user-attachments/assets/0c2b68cc-8e73-4ed5-8bd7-962b20f5dc68" />

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

## Images

<img width="3420" height="2138" alt="Screenshot 2025-12-19 at 11 40 50 AM" src="https://github.com/user-attachments/assets/4166bbc9-15d1-4475-8c18-2342121d1c43" />

<img width="3420" height="2146" alt="Screenshot 2025-12-19 at 11 40 59 AM" src="https://github.com/user-attachments/assets/5960cc5a-7d0b-481f-bf3e-3bd9b9878a50" />

<img width="3420" height="2137" alt="Screenshot 2025-12-19 at 11 40 23 AM" src="https://github.com/user-attachments/assets/8f6c20bd-7b8e-445d-a4ff-6f28beb4f8a0" />

