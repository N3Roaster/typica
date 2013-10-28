define(`__PageStart', `<html><head>
	<title>Typica - Data for Coffee Roasters</title>
	<link rel="stylesheet" type="text/css" href="style.css">
	</head><body><div id="page"><div id="topmatter">
	__SiteBanner
	__NavigationMenu
	</div>
	<div id="maintext">
')

define(`__PageEnd', `</div></div></body></html>')

define(`__SiteBanner', `<div id="topbanner">
	<img src="logo96.png" height="96px" width="96px" alt="Typica logo" />
	<h1>Typica</h1><h2>Data for Coffee Roasters</h2></div>
')

define(`__NavigationMenu', `<div id="menu">
	<a class="tab ifelse(__PageType, `Main', active", " href="index.html")>Typica</a>
	<a class="tab ifelse(__PageType, `Downloads', active", " href="downloads.html")>Downloads</a>
	<a class="tab ifelse(__PageType, `Documentation', active", " href="documentation.html")>Documentation</a>
	<a class="tab ifelse(__PageType, `Media', active", " href="media.html")>Photos and Videos</a>
	<a class="tab" href="http://appliedcoffeetechnology.tumblr.com/tagged/Typica">Blog</a>
	</div>
')

define(`__DownloadPage', `define(`__DownloadUrl', $1)
include(`src/pages/fragments/downloadfragment.m4')
')