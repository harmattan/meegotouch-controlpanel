# /bin/sh

# checks for incorrect catalogs of the applets,

wrongCatalogList()
{
    grep -i catalog /usr/lib/duicontrolpanel/*.desktop | cut -f 2 -d '=' |
    tr ',' '\n' | while read a; do
        ls /usr/share/l10n/meegotouch/$a* >/dev/null;
    done 2>&1 |
#    sed -e 's_/\([^/]*\)\*_\1_'
    sed -e 's_^.*/meegotouch/__' -e 's_.: No such file.*$__' |
    sort -u
}

# outputs all the desktop files which contains references to a
# non installed catalog
echo "The followings refers to non existant catalogs:"
wrongCatalogList | while read catalog; do
    grep "catalog.*$catalog" /usr/lib/duicontrolpanel/*.desktop
done

echo

echo "The followings does not have X-translation-catalog key specified:"
grep -L X-translation-catalog /usr/lib/duicontrolpanel/*desktop

