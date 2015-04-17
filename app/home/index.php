<?php
session_start();

if( !isset($_SESSION["username"]) ){
	displayLogin();
}else{
	displayHomePage();
}

function displayLogin(){
	header( "Location: ../login.php" );
}

function displayHomePage(){

	include '../common/header.php';
?>

        <div id="page-wrapper">

            <div class="container-fluid">

                <!-- Page Heading -->
                <div class="row">
                    <div class="col-lg-12">
                        <h1 class="page-header">
                            All Recipes <small>John Doe's Recipes</small>
							
							<div class="dropdown pull-right">
							<button class="btn btn-default dropdown-toggle" type="button" id="dropdownMenu1" data-toggle="dropdown" aria-expanded="true">
							Add recipe
								<span class="caret"></span>
							</button>
							<ul class="dropdown-menu" role="menu" aria-labelledby="dropdownMenu1">
								<li role="presentation"><a role="menuitem" tabindex="-1" href="#">Create new recipe</a></li>
								<li role="presentation"><a role="menuitem" tabindex="-1" href="#">Add existing recipe</a></li>								
							</ul>
							
                        </h1>
                    </div>
                </div>
                <!-- /.row -->

                <div class="row">
				<?php
				try{
					//get user recipes
					$sql = "SELECT * FROM recipe WHERE author = :username";
					$result = $conn->prepare($sql);
					$result->bindValue(":username", $_SESSION["username"], PDO::PARAM_STR);
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
    <script src="../js/jquery.js"></script>

    <!-- Bootstrap Core JavaScript -->
    <script src="../js/bootstrap.min.js"></script>

    <!-- Morris Charts JavaScript -->
    <script src="../js/plugins/morris/raphael.min.js"></script>
    <script src="../js/plugins/morris/morris.min.js"></script>
    <script src="../js/plugins/morris/morris-data.js"></script>

</body>

</html>
<?php
}
?>