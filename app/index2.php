<?php
session_start();

if( !isset($_SESSION["username"]) ){
	displayDefaultPage();
}else{
	displayHomePage();
}

function displayHomePage(){
	header( "Location: login.php" );
}

function displayDefaultPage(){
	//connect to DB
	include 'db/connectDatabase.php';
?>
<!DOCTYPE html>
<html lang="en">

<head>

    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="">
    <meta name="author" content="">

    <title>Cookbook Application</title>

    <!-- Bootstrap Core css -->
    <link href="css/bootstrap.min.css" rel="stylesheet">

    <!-- Custom css -->
    <link href="css/style.css" rel="stylesheet">

    <!-- Morris Charts css -->
    <link href="css/plugins/morris.css" rel="stylesheet">

    <!-- Custom Fonts -->
    <link href="../font-awesome/css/font-awesome.css" rel="stylesheet" type="text/css">

    <!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
        <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
        <script src="https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js"></script>
    <![endif]-->

</head>

<body>

    <div id="wrapper">

        <!-- Navigation -->
        <nav class="navbar navbar-inverse navbar-fixed-top" role="navigation">
            <!-- Brand and toggle get grouped for better mobile display -->
            <div class="navbar-header">
                <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-ex1-collapse">
                    <span class="sr-only">Toggle navigation</span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                </button>
                <a class="navbar-brand" href="/">Cookbook Application</a>
            </div>
            <!-- Top Menu Items -->
            <ul class="nav navbar-right top-nav">
                <li class="dropdown">
                    <a href="#" class="dropdown-toggle" data-toggle="dropdown"><i class="fa fa-user"></i>
					Guest
					<b class="caret"></b></a>
                    <ul class="dropdown-menu">
                        <li>
                            <a href="login.php"><i class="fa fa-fw fa-user"></i> Login</a>
                        </li>
                    </ul>
                </li>
            </ul>
            
            <!-- Search Bar -->
            <div class="col-sm-3 col-md-3 pull-right">
        <form action="search.php" method="POST" class="navbar-form" role="search">
            <div class="input-group">
                <input type="text" class="form-control" placeholder="Search" name="srch-term" id="srch-term">
                    <div class="input-group-btn">
                        <button class="btn btn-default" type="submit"><i class="glyphicon glyphicon-search"></i></button>
                    </div>
            </div>
        </form>
        </div>
            <!-- Sidebar Menu Items - These collapse to the responsive navigation menu on small screens -->
            <div class="collapse navbar-collapse navbar-ex1-collapse">
                <ul class="nav navbar-nav side-nav">
                    <li class="active">
                        <a href="/recipe"><span class="glyphicon glyphicon-apple"></span> All Recipes</a>
                    </li>
                </ul>
            </div>
            <!-- /.navbar-collapse -->
        </nav>

        <div id="page-wrapper">

            <div class="container-fluid">

                <!-- Page Heading -->
                <div class="row">
                    <div class="col-lg-12">
                        <h1 class="page-header">
                            All Recipes <small></small>
                        </h1>
                    </div>
                </div>
                <!-- /.row -->

                <div class="row">
				<?php
				try{
					//get user recipes
					$sql = "SELECT * FROM recipe";
					$result = $conn->prepare($sql);
					$result-> execute();
					
					$count = 1;
					
					while( $recipe = $result->fetch() ){
						print("
							<div class='col-lg-3'>
							<a href='../recipe?recipe=$recipe[ID]'>
								<div class='panel panel-default'>
									<div class='panel-heading'>
										<h3 class='panel-title'><i class=''></i>$recipe[name]</h3>
									</div>
									<div class='panel-body'>
										<img src='../img/default.jpg' class='img-responsive' alt='default' width='100%' height='100%'>
									</div>
								</div>
							</a>
							</div>
						");
					
						//start a new row every 3rd recipe
						if($count++ % 3 == 0){
							print("</div><div class='row'>");
						}
					}
				}catch(PDOException $e){
					//do nothing
				}
				?>

            </div>
            <!-- /.container-fluid -->

        </div>
        <!-- /#page-wrapper -->

    </div>
    <!-- /#wrapper -->

    <!-- jQuery -->
    <script src="js/jquery.js"></script>

    <!-- Bootstrap Core JavaScript -->
    <script src="js/bootstrap.min.js"></script>

    <!-- Morris Charts JavaScript -->
    <script src="js/plugins/morris/raphael.min.js"></script>
    <script src="js/plugins/morris/morris.min.js"></script>
    <script src="js/plugins/morris/morris-data.js"></script>

</body>

</html>
<?php
}
?>