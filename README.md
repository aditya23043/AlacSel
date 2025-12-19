<img width="3420" height="2224" alt="Screenshot 2025-12-19 at 11 40 33 AM" src="https://github.com/user-attachments/assets/132bdc29-c705-4b1a-b302-df77bccbcb11" />


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

<img width="3420" height="2224" alt="Screenshot 2025-12-19 at 11 40 23 AM" src="https://github.com/user-attachments/assets/473d25de-fc4d-42a6-b80a-2f41514a480e" />

<img width="3420" height="2224" alt="Screenshot 2025-12-19 at 11 40 50 AM" src="https://github.com/user-attachments/assets/0f5339db-7695-46e4-a07f-02c882a19c40" />

<img width="3420" height="2224" alt="Screenshot 2025-12-19 at 11 40 59 AM" src="https://github.com/user-attachments/assets/23a5aca0-78c3-40ba-92ae-a6a55fd8a9b0" />

