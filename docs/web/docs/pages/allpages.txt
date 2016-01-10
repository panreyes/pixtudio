     OLD:
    From namespaces other than the general one, including redirects:
    <dpl>
    notnamespace=
    titlematch=%
    redirects = include
    format = ,,,
    resultsheader = %PAGES%\n
    </dpl>
    From the general namespace, without redirects:
    <dpl>
    namespace=
    titlematch=%
    format = ,,,
    resultsheader = %PAGES%\n
    </dpl>
    From the general namespace, the redirects:
    <dpl>
    namespace=
    titlematch=%
    redirects = only
    format = ,,,
    resultsheader = %PAGES%\n
    </dpl>
    ==========
    <dpl>
    notnamespace=
    titlematch=%
    redirects = include
    format = ,,\n\n[[%PAGE%]],
    </dpl>
    <dpl>
    namespace=
    titlematch=%
    format = ,,\n\n[[%PAGE%]],
    </dpl>
    <dpl>
    namespace=
    titlematch=%
    redirects = only
    format = ,,\n\n[[%PAGE%]],
    </dpl>

All, A-C: <dpl> titleregexp=\^\[A-C\].\*\$ redirects = include format =
,,, resultsheader = %PAGES%\\n </dpl> All, D-F: <dpl>
titleregexp=\^\[D-F\].\*\$ redirects = include format = ,,,
resultsheader = %PAGES%\\n </dpl> All, G-I: <dpl>
titleregexp=\^\[G-I\].\*\$ redirects = include format = ,,,
resultsheader = %PAGES%\\n </dpl> All, J-L: <dpl>
titleregexp=\^\[J-L\].\*\$ redirects = include format = ,,,
resultsheader = %PAGES%\\n </dpl> All, M-O: <dpl>
titleregexp=\^\[M-O\].\*\$ redirects = include format = ,,,
resultsheader = %PAGES%\\n </dpl> All, P-R: <dpl>
titleregexp=\^\[P-R\].\*\$ redirects = include format = ,,,
resultsheader = %PAGES%\\n </dpl> All, S-U: <dpl>
titleregexp=\^\[S-U\].\*\$ redirects = include format = ,,,
resultsheader = %PAGES%\\n </dpl> All, V-X: <dpl>
titleregexp=\^\[V-X\].\*\$ redirects = include format = ,,,
resultsheader = %PAGES%\\n </dpl> All, Y-Z: <dpl>
titleregexp=\^\[Y-Z\].\*\$ redirects = include format = ,,,
resultsheader = %PAGES%\\n </dpl> All, rest: <dpl>
titleregexp=\^\[\^A-Z\].\*\$ redirects = include format = ,,,
resultsheader = %PAGES%\\n </dpl> ========== <dpl>
titleregexp=\^\[A-C\].\*\$ redirects = include format =
,,\\n\\n[%PAGE%](%PAGE% "wikilink"), </dpl> <dpl>
titleregexp=\^\[D-F\].\*\$ redirects = include format =
,,\\n\\n[%PAGE%](%PAGE% "wikilink"), </dpl> <dpl>
titleregexp=\^\[G-I\].\*\$ redirects = include format =
,,\\n\\n[%PAGE%](%PAGE% "wikilink"), </dpl> <dpl>
titleregexp=\^\[J-L\].\*\$ redirects = include format =
,,\\n\\n[%PAGE%](%PAGE% "wikilink"), </dpl> <dpl>
titleregexp=\^\[M-O\].\*\$ redirects = include format =
,,\\n\\n[%PAGE%](%PAGE% "wikilink"), </dpl> <dpl>
titleregexp=\^\[P-R\].\*\$ redirects = include format =
,,\\n\\n[%PAGE%](%PAGE% "wikilink"), </dpl> <dpl>
titleregexp=\^\[S-U\].\*\$ redirects = include format =
,,\\n\\n[%PAGE%](%PAGE% "wikilink"), </dpl> <dpl>
titleregexp=\^\[V-X\].\*\$ redirects = include format =
,,\\n\\n[%PAGE%](%PAGE% "wikilink"), </dpl> <dpl>
titleregexp=\^\[Y-Z\].\*\$ redirects = include format =
,,\\n\\n[%PAGE%](%PAGE% "wikilink"), </dpl> <dpl>
titleregexp=\^\[\^A-Z\].\*\$ redirects = include format =
,,\\n\\n[%PAGE%](%PAGE% "wikilink"), </dpl>
