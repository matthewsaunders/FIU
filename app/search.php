    <?php

        include("db/connectDatabase.php");
        $term = $_POST['srch-term'];

        $search = mysql_real_escape_string(trim($term));

        $keys = explode(" ",$search);
    
        $sql="SELECT * FROM `recipe` WHERE `name` LIKE '%$search%'";
        echo "$sql <br />";
        $find_recipes = mysql_query($sql) or die(mysql_error());

        while($row = mysql_fetch_assoc($find_recipes))
        {
            $name = $row['name'];
            
            echo $name.'<br />';
        }
        

/*
        include("db/connectDatabase.php");

        $sql="SELECT * FROM recipes";
        $query = mysqli_query($conn, $sql);
        $row = mysqli_fetch_row($query);
        
        $rows = $row[0];
        $page_rows = 10;
        $last = ceil($rows/$page_rows);
        if($last < 1)
        {
            $last = 1;
        }

        $pagenum = 1;

        if(isset($_GET['pn'])){
            $pagenum = preg_replace('#[^0-9]#', '', $_GET['pn']);
        }
                                
        if($pagenum < 1) {
            $pagenum = 1;
        }
        
        else if ($pagenum > $last) {
            $pagenum = $last;
        }
                    
        $limit = 'LIMIT ' .($pagenum - 1) * $page_rows .',' .$page_rows;
        $sql = "SELECT * FROM recipes WHERE name LIKE %$search% ORDER BY name DESC $limit"; 
        $query = mysqli_query($conn, $sql);
        $textline1 = "Recipes (<b>$rows</b>)";
        $textline2 = "Page <b>$pagenum</b> of <b>$last</b>";
        $paginationCtrls = '';
        if($last != 1){
            if($pagenum > 1) {
                $previous = $pagenum - 1;
                $paginationCtrls .= '<a href="'.$_SERVER['PHP_SELF'].'?pn='.$previous.'">Previous</a> &nbsp;';
            
            for($i = $pagenum-4; $i < $pagenum; $i++){
                if($i > 0) {
                    $paginationCtrls .= '<a href="'.$_SERVER['PHP_SELF'].'?pn='.$i.'">'.$i.'</a> &nbsp;';
                }
            }
        }
        
                                
        $paginationCtrls .= ''.$pagenum.' &nbsp; ';
        for($i = $pagenum+1; $i <= $last; $i++){
            $paginationCtrls .= '<a href="'.$SERVER['PHP_SELF'].'?pn='.$i.'</a> &nbsp; ';
            if($i >= $pagenum+4){
                break;
            }
        }
        
        if ($pagenum != $last) {
            $next = $pagenum + 1;
            $paginationCtrls .= ' &nbsp; &nbsp; <a href="'.$_SERVER['PHP_SELF'].'?pn='.$next.'">Next</a> ';
        }
     }
                                    
    $list = '';
    while($row = mysqli_fetch_array($query, MYSQLI_ASSOC)){
        $name = $row["name"];
        $author = $row["author"];
        $cooktime = $row["cooktime"];
        $difficulty = $row["difficulty"];
        $instructions = $row["instructions"];
        $list .= '<p>'.$name.' '.$author.' '.$cooktime.' '.$difficulty.' '.$instructions.'</p>';
    }
    mysqli_close($conn);
*/
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

    <!-- Bootstrap Core CSS -->
    <link href="css/bootstrap.min.css" rel="stylesheet">

    <!-- Custom CSS -->
    <link href="css/style.css" rel="stylesheet">

    <!-- Morris Charts CSS -->
    <link href="css/plugins/morris.css" rel="stylesheet">

    <!-- Custom Fonts -->
    <link href="font-awesome/css/font-awesome.css" rel="stylesheet" type="text/css">

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
                <a class="navbar-brand" href="index.html">Cookbook Application</a>
            </div>
            <!-- Top Menu Items -->
            <ul class="nav navbar-right top-nav">
                <li class="dropdown">
                    <a href="#" class="dropdown-toggle" data-toggle="dropdown"><i class="fa fa-envelope"></i> <b class="caret"></b></a>
                    <ul class="dropdown-menu message-dropdown">
                        <li class="message-preview">
                            <a href="#">
                                <div class="media">
                                    <span class="pull-left">
                                        <img class="media-object" src="http://placehold.it/50x50" alt="">
                                    </span>
                                    <div class="media-body">
                                        <h5 class="media-heading"><strong>John Smith</strong>
                                        </h5>
                                        <p class="small text-muted"><i class="fa fa-clock-o"></i> Yesterday at 4:32 PM</p>
                                        <p>Coming Soon...</p>
                                    </div>
                                </div>
                            </a>
                        </li>
                        <li class="message-footer">
                            <a href="#">Read All New Messages</a>
                        </li>
                    </ul>
                </li>
                <li class="dropdown">
                    <a href="#" class="dropdown-toggle" data-toggle="dropdown"><i class="fa fa-bell"></i> <b class="caret"></b></a>
                    <ul class="dropdown-menu alert-dropdown">
                        <li>
                            <a href="#">Coming Soon <span class="label label-default">Alert</span></a>
                        </li>
                        <li class="divider"></li>
                        <li>
                            <a href="#">View All</a>
                        </li>
                    </ul>
                </li>
                <li class="dropdown">
                    <a href="#" class="dropdown-toggle" data-toggle="dropdown"><i class="fa fa-user"></i> John Smith <b class="caret"></b></a>
                    <ul class="dropdown-menu">
                        <li>
                            <a href="#"><i class="fa fa-fw fa-user"></i> Profile</a>
                        </li>
                        <li>
                            <a href="#"><i class="fa fa-fw fa-gear"></i> Settings</a>
                        </li>
                        <li class="divider"></li>
                        <li>
                            <a href="#"><i class="fa fa-fw fa-power-off"></i> Log Out</a>
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
                    <li>
                        <a href="index.html"><span class="glyphicon glyphicon-apple"></span> All Recipes</a>
                    </li>
					<li class="divider"></li>
                    <li>
                        <a href="javascript:;" data-toggle="collapse" data-target="#booklist"><span class="glyphicon glyphicon-book"></span> Cookbooks <i class="fa fa-fw fa-caret-down"></i></a>
                        <ul id="booklist" class="collapse">
                            <li>
                                <a href="#">Breakfast</a>
                            </li>
                            <li>
                                <a href="#">Lunch</a>
                            </li>
							<li>
                                <a href="#">Cena</a>
                            </li>
							<li>
                                <a href="#">Pastellitos</a>
                            </li>
                        </ul>
                    </li>
					<li>
                        <a href="index.html"><span class="glyphicon glyphicon-plus-sign"></span> Add a Cookbook</a>
                    </li>
                </ul>
            </div>
            <!-- /.navbar-collapse -->
        </nav>

        <div id="page-wrapper">

            <div class="container-fluid">
            <div class="container">

    <hgroup class="mb20">
		<h1>Search Results</h1>
		<h2 class="lead"><strong class="text-danger"><?php echo "2"; ?></strong> results were found for the search for <strong class="text-danger"><?php ?></strong></h2>
        <h2 class="lead">See search results for <a href="#"><strong class="text-danger">Almuerzo</strong></a>?</h2>								
	</hgroup>

<!--
    <section class="col-xs-12 col-sm-6 col-md-12">
		<article class="search-result row">
			<div class="col-xs-12 col-sm-12 col-md-3">
				<a href="#" title="Lorem ipsum" class="thumbnail"><img src="img/omelette.jpg" alt="omlette" /></a>
			</div>
			<div class="col-xs-12 col-sm-12 col-md-2">
				<ul class="meta-search">
					<li><i class="glyphicon glyphicon-calendar"></i> <span>03/24/2015</span></li>
					<li><i class="glyphicon glyphicon-time"></i> <span>4:28 pm</span></li>
				</ul>
			</div>
			<div class="col-xs-12 col-sm-12 col-md-7 excerpet">
				<h3><a href="#" title="">Omelette Du Fromage</a></h3>
				<p>An omelette with cheese.</p>						
                <span class="plus"><a href="#" title="Add Omelette Du Fromage"><i class="glyphicon glyphicon-plus"></i></a></span>
			</div>
			<span class="clearfix borda"></span>
		</article>

        <article class="search-result row">
			<div class="col-xs-12 col-sm-12 col-md-3">
				<a href="#" title="Lorem ipsum" class="thumbnail"><img src="img/breakfast.jpg" alt="Pancakes" /></a>
			</div>
			<div class="col-xs-12 col-sm-12 col-md-2">
				<ul class="meta-search">
					<li><i class="glyphicon glyphicon-calendar"></i> <span>03/24/2015</span></li>
					<li><i class="glyphicon glyphicon-time"></i> <span>8:32 pm</span></li>
				</ul>
			</div>
			<div class="col-xs-12 col-sm-12 col-md-7">
				<h3><a href="#" title="">Pancakes</a></h3>
				<p>A timeless classic prepared right.</p>						
                <span class="plus"><a href="#" title="Add Pancakes"><i class="glyphicon glyphicon-plus"></i></a></span>
			</div>
			<span class="clearfix borda"></span>
		</article>
-->
	</section>
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
