echo "[#] Building mod..."
./ttyd-mod-manager -r . build
echo "[#] Converting to iso..."
dolphin-tool convert -i patch/P-G8ME/sys/main.dol -o main.iso -f iso
echo "[#] Generating delta..."
xdelta3 -f -e -s ./TTYD_US.iso main.iso mod.xdelta
