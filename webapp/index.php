<!DOCTYPE html>
<html>
<head>
	<title>RasPy Control Panel</title>
	<meta content="">
	<link rel="shortcut icon" type="image/png" href="assets/img/favicon.png">
	<link rel="stylesheet" href="assets/css/main.css">
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
	<script src="assets/js/datatransfer.js"></script>
	<script src="assets/js/app.js"></script>
</head>
<body>
	<div id="transition-layer"></div>
	<div id="page">
		<header>
			<!-- TODO?: HEADER -->
		</header>
		<nav>
			<ul class="main-navigation">
				<li>
					<a href="#summary"> Summary</a>
				</li>
				<li class="selected">
					<a href="#home"> Home</a>
				</li>
				<li>
					<a href="#alerts"> Alerts</a>
				</li>
				<li>
					<a href="#log"> Log</a>
				</li>
			</ul>
			<aside>
				<a href="#settings"></a>
				<a href="#exit"></a>
			</aside>
			<div id="nav-indicator"></div>
		</nav>


		<div id="content">

			<div class="content-slider">
				<?php include('templates/summary-page.php') ?>
				<?php include('templates/home-page.php') ?>
				<?php include('templates/alerts-page.php') ?>
				<?php include('templates/log-page.php') ?>
			</div>

		</div>

		<?php include('templates/settings-page.php') ?>
		<?php include('templates/exit-page.php') ?>
		
		<footer>
			<ul class="footer-navigation">
				<li>
					<a href="#red">RED</a>
				</li>
				<li>
					<a href="#yellow">YELLOW</a>
				</li>
				<li>
					<a href="#green">GREEN</a>
				</li>
			</ul>
		</footer>
	</div>
</body>
</html>