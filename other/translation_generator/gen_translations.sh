# /bin/bash
tmpdir=/tmp/dtranslations
outdirprefix="/scratchbox/users/manni/targets/harmattan-x86-prerelease/usr/share/l10n/dui"
# outdirprefix="/scratchbox/users/manni/targets/harmattan-x86/usr/share/l10n/dui"
# outdirprefix="/usr/share/l10n/dui"
loc1="en"
loc2="de"
tmpf1="$tmpdir/$loc1.ts"
tmpf2="$tmpdir/$loc2.ts"
outdir1="$outdirprefix/$loc1/LC_MESSAGES/"
outdir2="$outdirprefix/$loc2/LC_MESSAGES/"

mkdir -p $tmpdir

genheader(){
    echo "<?xml version=\"1.0\" encoding=\"utf-8\"?>
<!DOCTYPE TS>
<TS version=\"2.0\" sourcelanguage=\"C\" language=\"$1\"> 
<context>
   <name>message_context</name>"
}

genfooter(){
    echo "</context>
</TS>"
}

genmessage(){
    echo -n "    <message id=\"$1\">
        <source>$1</source>
        <translation>"
    echo -n "$2" | recode ..HTML_1.1
    echo "</translation>
    </message>"
}


# generate ts files:
genheader "$loc1" >"$tmpf1"
genheader "$loc2" >"$tmpf2"

cat gen_translations.files |
while read st; do
    cat "$st"
done |
egrep 'qtn|Id|Default' | tr ',' '\n' | grep -v '^\ *$' | cut -f 2 -d '"' |
while read key; do
    if ! echo "$key" | grep qtn &>/dev/null; then continue; fi
    read value
    if ! echo "$key" | grep qtn &>/dev/null; then echo "warning $value is a key"; fi
    genmessage "$key" "$value" >>"$tmpf1"
    genmessage "$key" "${value} $loc2" >>"$tmpf2"
done

genfooter >>"$tmpf1"
genfooter >>"$tmpf2"


# compile them:
mkdir -p "$outdir1"
lrelease "$tmpf1" -qm "$outdir1/duicontrolpanel.qm"
mkdir -p "$outdir2"
lrelease "$tmpf2" -qm "$outdir2/duicontrolpanel.qm"

