#/bin/sh

# cat "doc/header.html"
echo "
<table class="normal">
  <tr>
    <th>Name</th>
    <th>Translation id</th>
    <th>Ids maintained for compatibility</th>
  </tr>"

for i in ../controlpanel/categories/*.cpcategory; do
    echo "  <tr>"
    grep -E '^Name|^Aliases' "$i" \
    | cut -f 2 -d '=' | sed 's_^_     <td>_;s_$_</td>_'

    echo "  </tr>"
done

echo "</table>"
# cat "doc/footer.html"

