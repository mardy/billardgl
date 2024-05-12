#! /bin/sh

set -e

TMPDIR="$(mktemp -d)"
OUTDIR="$TMPDIR/billardgl"

mkdir -p "$OUTDIR"
cp -a lang Texturen wii/meta.xml wii/icon.png "$OUTDIR"
cp wii/BillardGL.conf.v7 "$OUTDIR/.BillardGL.conf.v7"
cp BillardGL.dol "$OUTDIR/boot.dol"

cd $TMPDIR
zip -r billardgl.zip billardgl
cd -
mv "$TMPDIR/billardgl.zip" .
rm -rf "$TMPDIR"
