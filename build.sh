echo "[#] Building mod..."
./ttyd-mod-manager -r . build
echo "[#] Generating delta..."
./mpatch -s TTYD_US.iso -i patch/P-G8ME -p mod.xdelta
echo "[#] Creating handout..."
cp mod.xdelta mpatch handout/
tar -acvf handout.tar.gz handout/
