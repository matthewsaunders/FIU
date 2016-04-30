<?php
session_start();

//user needs to login
if( !isset($_SESSION['username']) ){
	displayLogin();
}

include '../db/connectDatabase.php';
try{
	//get user profile
	$sql = "SELECT * FROM users WHERE name = :username";
	$result = $conn->prepare($sql);
	$result->bindValue(":username", $_SESSION["username"], PDO::PARAM_STR);
	$result-> execute();
	$profile = $result->fetch();
}catch(PDOException $e){
	$conn = null;
	print($e->getMessage()."<br>");
}
	
$recipeExists = false;

//user wants to display existing recipe
if( isset($_GET["recipe"]) ){
	try{
		//get recipe to edit
		$sql = "SELECT * FROM recipe WHERE ID = :recipeID";
		$result = $conn->prepare($sql);
		$result->bindValue(":recipeID", $_GET['recipe'], PDO::PARAM_INT);
		$result-> execute();
		
		if( $recipeEditing = $result->fetch() ){
			if( $recipeEditing['author'] == $_SESSION["username"] || $profile['adminStatus'] == "Y"  ){
				$recipeExists = true;
			}
		}
	}catch(PDOException $e){
		$conn = null;
		print($e->getMessage()."<br>");
	}
	
	displayRecipeForm($conn, $profile, $recipeEditing, $recipeExists);
}elseif( isset($_POST["submit"]) ){
	if( isset($_POST['recipe-id']) ){
		//user has submitted recipe form
		try{
			//get recipe to edit
			$sql = "SELECT * FROM recipe WHERE ID = :recipeID";
			$result = $conn->prepare($sql);
			$result->bindValue(":recipeID", $_POST['recipe-id'], PDO::PARAM_INT);
			$result-> execute();
				
			if( $recipeEditing = $result->fetch() ){
				if( $recipeEditing['author'] == $_SESSION["username"] || $profile['adminStatus'] == "Y" ){
					$recipeExists = true;
				}
			}
		}catch(PDOException $e){
			$conn = null;
			print($e->getMessage()."<br>");
		}
	}
		
	if( $recipeExists ){
		//updat existing record
		updateDB($conn, $profile, $recipeEditing);
	}else{
		//create new record
		createInDB($conn, $profile);
	}
}else{
	//user is creating new recipe
	displayRecipeForm($conn, $profile, NULL, $recipeExists);
}

function displayLogin(){
	header( "Location: ../login.php" );
}

function createInDB($conn, $profile){
	include '../db/connectDatabase.php';
	
	if( isset($_POST["recipe-hours"]) and $_POST["recipe-hours"] >= 0 ){
		$hours = $_POST["recipe-hours"];
	}else{
		$hours = 0;
	}
		
	if( isset($_POST["recipe-minutes"]) and $_POST["recipe-minutes"] >= 0 ){
		$minutes = $_POST["recipe-minutes"];
	}else{
		$minutes = 0;
	}

	$cooktime = $hours*60 + $minutes;
	
	try{
		//insert recipe into DB
		$sql = "INSERT INTO recipe (name, author, cooktime, difficulty, instructions) VALUES (:name, :author, :cooktime, :difficulty, :instructions)";
		$result = $conn->prepare($sql);
		$result->bindValue(":name", trim($_POST['recipe-name']), PDO::PARAM_STR);
		$result->bindValue(":author", trim($_POST['recipe-author']), PDO::PARAM_STR);
		$result->bindValue(":cooktime", $cooktime, PDO::PARAM_INT);
		$result->bindValue(":difficulty", trim($_POST['recipe-difficulty']), PDO::PARAM_STR);
		$result->bindValue(":instructions", trim($_POST['recipe-instructions']), PDO::PARAM_STR);
		$result-> execute();
		$recipeId = $conn->lastInsertId();
	}catch(PDOException $e){
		//$conn = null;
		print($e->getMessage()."<br>");
	}
	
	$count = 1;
	while( isset($_POST["recipe-ingredient-name-".$count]) ){
		try{
			//check if ingredient exists
			$sql = "SELECT * FROM ingredient WHERE name = :name";
			$result = $conn->prepare($sql);
			$result->bindValue(":name", $_POST["recipe-ingredient-name-".$count], PDO::PARAM_STR);
			$result-> execute();
			
			if( !($ingredient = $result->fetch()) ){
				//ingredient does not already exist, add it to db
				$sql = "INSERT INTO ingredient (name, measurementUnit) VALUES (:name, :measurementUnit)";
				$result = $conn->prepare($sql);
				$result->bindValue(":name", $_POST["recipe-ingredient-name-".$count], PDO::PARAM_STR);
				$result->bindValue(":measurementUnit", $_POST["recipe-ingredient-unit-".$count], PDO::PARAM_STR);
				$result-> execute();
			}
				
			//add ingredient and recipe to containsIngredient
			$sql = "INSERT INTO containsIngredient (recipeId, ingredientName, amount) VALUES (:recipeId, :ingredientName, :amount)";
			$result = $conn->prepare($sql);
			$result->bindValue(":recipeId", $recipeId, PDO::PARAM_INT);
			$result->bindValue(":ingredientName", $_POST["recipe-ingredient-name-".$count], PDO::PARAM_STR);
			$result->bindValue(":amount", $_POST["recipe-ingredient-amount-".$count], PDO::PARAM_STR);
			$result-> execute();
		}catch(PDOException $e){
			$conn = null;
			print($e->getMessage()."<br>");
		}
		
		//move on to the next ingredient
		$count++;
	}
	header( "Location: ../recipe?recipe=$recipeId" );
}

function updateDB($conn, $profile, $recipeEditing){
	include '../db/connectDatabase.php';
	
	if( isset($_POST["recipe-hours"]) and $_POST["recipe-hours"] >= 0 ){
		$hours = $_POST["recipe-hours"];
	}else{
		$hours = 0;
	}
		
	if( isset($_POST["recipe-minutes"]) and $_POST["recipe-minutes"] >= 0 ){
		$minutes = $_POST["recipe-minutes"];
	}else{
		$minutes = 0;
	}

	$cooktime = $hours*60 + $minutes;
	
	try{
		//update recipe in DB
		$sql = "UPDATE recipe SET name = :name, cooktime = :cooktime, difficulty = :difficulty, instructions = :instructions WHERE ID = :recipeId";
		$result = $conn->prepare($sql);
		$result->bindValue(":recipeId", $recipeEditing['ID'], PDO::PARAM_INT);
		$result->bindValue(":name", trim($_POST['recipe-name']), PDO::PARAM_STR);
		$result->bindValue(":cooktime", $cooktime, PDO::PARAM_INT);
		$result->bindValue(":difficulty", trim($_POST['recipe-difficulty']), PDO::PARAM_INT);
		$result->bindValue(":instructions", $_POST['recipe-instructions'], PDO::PARAM_STR);
		$result-> execute();
	}catch(PDOException $e){
		//$conn = null;
		print($e->getMessage()."<br>");
	}
	
	$count = 1;
	while( isset($_POST["recipe-ingredient-name-".$count]) ){
		try{
			//check if ingredient exists
			$sql = "SELECT * FROM ingredient WHERE name = :name";
			$result = $conn->prepare($sql);
			$result->bindValue(":name", $_POST["recipe-ingredient-name-".$count], PDO::PARAM_STR);
			$result-> execute();
			
			if( !($ingredient = $result->fetch()) ){
				//ingredient does not already exist, add it to db
				$sql = "INSERT INTO ingredient (name, measurementUnit) VALUES (:name, :measurementUnit)";
				$result = $conn->prepare($sql);
				$result->bindValue(":name", $_POST["recipe-ingredient-name-".$count], PDO::PARAM_STR);
				$result->bindValue(":measurementUnit", $_POST["recipe-ingredient-unit-".$count], PDO::PARAM_STR);
				$result-> execute();
			}
			
			//check if ingredient exists in containsIngredient
			$sql = "SELECT * FROM containsIngredient WHERE recipeId=:recipeId AND ingredientName=:ingredientName";
			$result = $conn->prepare($sql);
			$result->bindValue(":recipeId", $recipeEditing['ID'], PDO::PARAM_STR);
			$result->bindValue(":ingredientName", $_POST["recipe-ingredient-name-".$count], PDO::PARAM_STR);
			$result-> execute();
			
			if( !($containsIngredient = $result->fetch()) ){
				//add ingredient and recipe to containsIngredient
				$sql = "INSERT INTO containsIngredient (recipeId, ingredientName, amount) VALUES (:recipeId, :ingredientName, :amount)";
				$result = $conn->prepare($sql);
				$result->bindValue(":recipeId", $recipeEditing['ID'], PDO::PARAM_INT);
				$result->bindValue(":ingredientName", $_POST["recipe-ingredient-name-".$count], PDO::PARAM_STR);
				$result->bindValue(":amount", $_POST["recipe-ingredient-amount-".$count], PDO::PARAM_STR);
				$result-> execute();
			}else{
				//update relationship
				$sql = "UPDATE containsIngredient SET amount=:amount WHERE recipeId=:recipeId AND ingredientName=:ingredientName";
				$result = $conn->prepare($sql);
				$result->bindValue(":recipeId", $recipeEditing['ID'], PDO::PARAM_INT);
				$result->bindValue(":ingredientName", $_POST["recipe-ingredient-name-".$count], PDO::PARAM_STR);
				$result->bindValue(":amount", $_POST["recipe-ingredient-amount-".$count], PDO::PARAM_STR);
				$result-> execute();
			}
		}catch(PDOException $e){
			$conn = null;
			print($e->getMessage()."<br>");
		}
		
		//move on to the next ingredient
		$count++;
	}
	header( "Location: ../recipe?recipe=".$recipeEditing['ID'] );
}

function displayRecipeForm($conn, $profile, $recipeEditing, $recipeExists){
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

    <!-- Bootstrap Core ../css -->
    <link href="../css/bootstrap.min.css" rel="stylesheet">

    <!-- Custom ../css -->
    <link href="../css/style.css" rel="stylesheet">

    <!-- Morris Charts ../css -->
    <link href="../css/plugins/morris.css" rel="stylesheet">

    <!-- Custom Fonts -->
    <link href="../font-awesome/css/font-awesome.css" rel="stylesheet" type="text/../css">

    <!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
        <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
        <script src="https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js"></script>
    <![endif]-->
	
	<script>
	//global count
	var count = 3;
	
	function addIngredient(){
		var blankIngredient = "<div class='input-group col-md-2 pull-right'> <input name='recipe-ingredient-unit-"+count+"' id='InputMessage' class='form-control' placeholder='Units'></input></div><div class='input-group col-md-2 pull-right'><input name='recipe-ingredient-amount-"+count+"' id='InputMessage' class='form-control' placeholder='Amount'></input></div><div class='input-group col-md-5 pull-right'><input name='recipe-ingredient-name-"+count+"' id='InputMessage' class='form-control' placeholder='Ingredient'></input></div><div style='clear:both'></div>";
		var div = document.getElementById('ingredient-block');
		div.innerHTML = div.innerHTML + blankIngredient;
		count++;
	}
	</script>
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
				<?php
				if( isset($_SESSION["username"]) ){
				?>
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
                                        <h5 class="media-heading"><strong>Management</strong>
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
                    <a href="#" class="dropdown-toggle" data-toggle="dropdown"><i class="fa fa-user"></i>
					<?php 
						print($profile["name"]);
					?>
					<b class="caret"></b></a>
                    <ul class="dropdown-menu">
                        <li>
                            <a href="#"><i class="fa fa-fw fa-user"></i> Profile</a>
                        </li>
                        <li>
                            <a href="#"><i class="fa fa-fw fa-gear"></i> Settings</a>
                        </li>
                        <li class="divider"></li>
                        <li>
                            <a href="../login.php?action=logout"><i class="fa fa-fw fa-power-off"></i> Log Out</a>
                        </li>
                    </ul>
                </li>
			<?php
			}else{
			?>
				<li class="dropdown">
                    <a href="#" class="dropdown-toggle" data-toggle="dropdown"><i class="fa fa-user"></i>
					Guest
					<b class="caret"></b></a>
                    <ul class="dropdown-menu">
                        <li>
                            <a href="../login.php"><i class="fa fa-fw fa-user"></i> Login</a>
                        </li>
                    </ul>
                </li>
			<?php
			}
			?>
			</ul>
			
            <!-- Search Bar -->
            <div class="col-sm-3 col-md-3 pull-right">
                <form class="navbar-form" role="search">
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
                        <a href="../recipe"><i class="fa fa-cutlery"></i> All Recipes</a>
                    </li>
					<li class="divider"></li>
					<?php
					if( $profile['adminStatus'] == "Y" ){
						print("
						<li>
							<a href='../ingredient'><span class='glyphicon glyphicon-apple'></span> All Ingredients</a>
						</li>
						");
					}
					?>
					<?php
					if( isset($_SESSION["username"]) ){
					?>
					<li class="divider"></li>
					<li>
                        <a href="/"><span class="fa fa-bookmark"></span> My Recipes</a>
                    </li>
						<li>
							<a href="javascript:;" data-toggle="collapse" data-target="#booklist"><span class="glyphicon glyphicon-book"></span> Cookbooks <i class="fa fa-fw fa-caret-down"></i></a>
							<ul id="booklist" class="collapse">
							<?php
							try{
								//get user cookbooks
								$sql = "SELECT * FROM cookbook WHERE author = :username";
								$result = $conn->prepare($sql);
								$result->bindValue(":username", $_SESSION["username"], PDO::PARAM_STR);
								$result-> execute();
								
								while( $cookbook = $result->fetch() ){
									print("
										<li>
											<a href='../cookbook?cookbook=$cookbook[ID]'>$cookbook[name]</a>
										</li>
									");
								}
							}catch(PDOException $e){
								//do nothing
							}
							
							?>
							</ul>
						</li>
						<li>
							<a href="../cookbook/createEditCookbook.php"><span class="glyphicon glyphicon-plus-sign"></span> Add a Cookbook</a>
						</li>
					<?php
					}
					?>
                </ul>
            </div>
            <!-- /.navbar-collapse -->
        </nav>

        <div id="page-wrapper">

            <div class="container-fluid">
					<div class="row">
						<form role="form" action="createEditRecipe.php" method="post">
							<div class="col-lg-12">
								<?php
								if( isset($_GET['recipe']) ){
									print("<h2 class='text-center'>Edit Recipe</h2>");
								}else{
									print("<h2 class='text-center'>New Recipe</h2>");
								}
								?>
								
							</div>
							<div class="col-md-9">
								<div class="well well-sm"><strong><span class="glyphicon glyphicon-asterisk"></span>Required Field</strong></div>
								<div class="form-group">
									<label for="InputName" class="col-md-2">Name *</label>
									<div class="input-group col-md-10">
										<?php
										if( $recipeExists ){
											print('<input type="text" class="form-control" name="recipe-name" id="InputName" value="'.$recipeEditing["name"].'" required>');
										}else{
											print("<input type='text' class='form-control' name='recipe-name' id='InputName' placeholder='Enter Name' required>");
										}
										?>
									</div>
								</div>								
                                <div style="clear:both"></div> 
								
								<div class="form-group">
									<label for="InputDifficulty" class="col-md-2">Difficulty</label>
									<div class="btn-group" name="recipe-difficulty" role="group" aria-label="...">
                                      <?php
												if( $recipeExists and $recipeEditing['difficulty'] == 1){
													print("<input type='radio' class='btn btn-default' name='recipe-difficulty' value='1' checked>1</input><br>");
												}else{
													print("<input type='radio' class='btn btn-default' name='recipe-difficulty' value='1'>1</input><br>");
												}
												
												if( $recipeExists and $recipeEditing['difficulty'] == 2){
													print("<input type='radio' class='btn btn-default' name='recipe-difficulty' value='2' checked>2</input><br>");
													}else{
													print("<input type='radio' class='btn btn-default' name='recipe-difficulty' value='2'>2</input><br>");
												}
												
												if($recipeExists and $recipeEditing['difficulty'] == 3){
													print("<input type='radio' class='btn btn-default' name='recipe-difficulty' value='3' checked>3</input><br>");
													}else{
													print("<input type='radio' class='btn btn-default' name='recipe-difficulty' value='3'>3</input><br>");
												}
												
												if($recipeExists and $recipeEditing['difficulty'] == 4){
													print("<input type='radio' class='btn btn-default' name='recipe-difficulty' value='4' checked>4</input><br>");
													}else{
													print("<input type='radio' class='btn btn-default' name='recipe-difficulty' value='4'>4</input><br>");
												}
												
												if($recipeExists and $recipeEditing['difficulty'] == 5){
													print("<input type='radio' class='btn btn-default' name='recipe-difficulty' value='5' checked>5</input><br>");
													}else{
													print("<input type='radio' class='btn btn-default' name='recipe-difficulty' value='5'>5</input><br>");
												}
											?>
                                    </div>
								</div>
								<div class="form-group">
									<label for="InputEmail" class="col-md-2">Cooktime</label>
									<div class="input-group">
										<?php
											if( $recipeExists){
												$hours = intval($recipeEditing['cooktime'] / 60);
												$minutes = $recipeEditing['cooktime'] % 60;
											}
										?>
                                        <div class="col-md-4">
											<?php
											if($recipeExists){
												print('<input type="number" class="form-control" id="recipe-hours" name="recipe-hours" value='.$hours.'>');
											}else{
												print('<input type="number" class="form-control" id="recipe-hours" name="recipe-hours" placeholder="Hours">');
											}
											?>
                                        </div>
                                        <div class="col-md-4">
                                            <?php
											if($recipeExists){
												print("<input type='number' class='form-control' id='recipe-minutes' name='recipe-minutes' value=".$minutes.">");
											}else{
												print('<input type="number" class="form-control" id="recipe-minutes" name="recipe-minutes" placeholder="Minutes">');
											}
											?>
                                        </div>
                                    </div>
								</div>

								
                                <div class="form-group" id="ingredient-block">
                                    <label for="InputMessage" class="col-md-3 pull-left">Ingredients *</label>
									<?php
									if($recipeExists){
										try{
											//get ingredients
											$sql = "SELECT * FROM containsIngredient WHERE recipeId = :recipeID";
											$result = $conn->prepare($sql);
											$result->bindValue(":recipeID", $_GET["recipe"], PDO::PARAM_INT);
											$result-> execute();
												
											$count = 1;
											while( $ingredient = $result->fetch() ){
												$sql = "SELECT * FROM ingredient WHERE name = :ingredientName";
												$result2 = $conn->prepare($sql);
												$result2->bindValue(":ingredientName", trim($ingredient['ingredientName']), PDO::PARAM_STR);
												$result2-> execute();
												$unit = $result2->fetch();
												
												print("
													<div class='input-group col-md-2 pull-right'>
														<input name='recipe-ingredient-unit-$count' id='InputMessage' class='form-control' value='$unit[measurementUnit]'></input>
													</div>
													<div class='input-group col-md-2 pull-right'>
														<input name='recipe-ingredient-amount-$count' id='InputMessage' class='form-control' value='$ingredient[amount]'></input>
													</div>
													<div class='input-group col-md-5 pull-right'>
														<input name='recipe-ingredient-name-$count' id='InputMessage' class='form-control' value='$ingredient[ingredientName]'></input>
													</div>
													<div style='clear:both'></div>
												");
												$count++;
											}
										}catch(PDOException $e){
											//do nothing
										}
										print("
											<label for='InputMessage' class='col-md-2 pull-left'></label>
											<div class='input-group col-md-2 pull-right'>
												<input name='recipe-ingredient-unit-$count' id='InputMessage' class='form-control' placeholder='Units'></input>
											</div>
											<div class='input-group col-md-2 pull-right'>
												<input name='recipe-ingredient-amount-$count' id='InputMessage' class='form-control' placeholder='Amount'></input>
											</div>
											<div class='input-group col-md-5 pull-right'>
												<input name='recipe-ingredient-name-$count' id='InputMessage' class='form-control' placeholder='Ingredient'></input>
											</div>
											<div style='clear:both'></div>
										");
									}else{
										for($count = 1; $count <= 3; $count++){
											print("
											<div class='form-group'>
												<label for='InputMessage' class='col-md-2 pull-left'></label>
												<div class='input-group col-md-2 pull-right'>
													<input name='recipe-ingredient-unit-$count' id='InputMessage' class='form-control' placeholder='Units'></input>
												</div>
												<div class='input-group col-md-2 pull-right'>
													<input name='recipe-ingredient-amount-$count' id='InputMessage' class='form-control' placeholder='Amount'></input>
												</div>
												<div class='input-group col-md-5 pull-right'>
													<input name='recipe-ingredient-name-$count' id='InputMessage' class='form-control' placeholder='Ingredient'></input>
												</div>
											</div>
											<div style='clear:both'></div>
											");
										}
									}
									//update the count to javascript
									$count++;
									print("<script>count = $count</script>");
									?>
                                </div>
                                <div style="clear:both"></div>

                                
                                
                                <div class="form-group" style="margin-top:10px;">
                                    <button type="button" onclick="addIngredient()" class="btn btn-info col-md-offset-10">Add Ingredient</button>
                                    <br>
                                </div>
                                <div class="form-group">
									<label for="InputMessage" class="col-md-2">Cooking Instructions</label>
									<div class="input-group">
										<?php
										if($recipeExists){
											print('<textarea name="recipe-instructions" id="InputMessage" class="form-control" rows="5" required>'.$recipeEditing["instructions"].'</textarea>');
										}else{
											print('<textarea name="recipe-instructions" id="InputMessage" class="form-control" rows="5" required></textarea>');
										}
										?>
										<span class="input-group-addon"><span class="glyphicon glyphicon-asterisk"></span></span>
									</div>
								</div>
								
								<input type="hidden" name="recipe-author" value="
								<?php
								print($_SESSION["username"]);
								?>
								"></input>
								<div class="form-actions pull-right">
									<?php
									if( isset($_GET['recipe']) ){
										print("<input type='hidden' name='recipe-id' value='$recipeEditing[ID]'></input>");
									}
									?>
									<input type="submit" name="submit" value="Submit" class="btn btn-primary"></input>
									<?php
									print("
									<script>
									function cancelRemove(){
										location.href = '../recipe?recipe=".$recipeEditing['ID']."';
									}
									</script>
									");
									print("<button type='button' onclick='cancelRemove()' class='btn'>Cancel</button>");
									?>
								</div>	
							</div>
						</form>
					</div>
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