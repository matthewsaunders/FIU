<?php
//Attempt to create DB tables
print("<h4>Creating tables in DB</h4>");
try{
	$table = "cookbook";
	$sql = "CREATE table $table(
		ID INT(11) AUTO_INCREMENT PRIMARY KEY,
		name VARCHAR(150),
		author VARCHAR(100) NOT NULL);";
	$conn->exec($sql);
	print("....Created Table: $table <br>");
} catch (PDOException $e){
	print("....ERROR: Table '$table' already exists<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$table = "recipe";
	$sql = "CREATE table $table(
		ID INT(11) AUTO_INCREMENT PRIMARY KEY,
		name VARCHAR(150),
		author VARCHAR(100) NOT NULL,
		cooktime INT,
		difficulty INT(5),
		instructions TEXT);";
	$conn->exec($sql);
	print("....Created Table: $table <br>");
} catch (PDOException $e){
	print("....ERROR: Table '$table' already exists<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$table = "ingredient";
	$sql = "CREATE table $table(
		name VARCHAR(150) PRIMARY KEY,
		measurementUnit VARCHAR(100));";
	$conn->exec($sql);
	print("....Created Table: $table <br>");
} catch (PDOException $e){
	print("....ERROR: Table '$table' already exists<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$table = "users";
	$sql = "CREATE table $table(
		name VARCHAR(150) PRIMARY KEY,
		email VARCHAR(255) NOT NULL,
		password VARCHAR(50) NOT NULL,
		adminStatus CHAR(1) NOT NULL);";
	$conn->exec($sql);
	print("....Created Table: $table <br>");
} catch (PDOException $e){
	print("....ERROR: Table '$table' already exists<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$table = "containsRecipe";
	$sql = "CREATE table $table(
		cookbookId INT(11),
		recipeId INT(11),
		PRIMARY KEY(cookbookId, recipeId));";
	$conn->exec($sql);
	print("....Created Table: $table <br>");
} catch (PDOException $e){
	print("....ERROR: Table '$table' already exists<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$table = "containsIngredient";
	$sql = "CREATE table $table(
		recipeId INT(11),
		ingredientName VARCHAR(150),
		amount VARCHAR(10) NOT NULL,
		PRIMARY KEY(recipeId,ingredientName));";
	$conn->exec($sql);
	print("....Created Table: $table <br>");
} catch (PDOException $e){
	print("....ERROR: Table '$table' already exists<br>");
	//print("    ".print($e->getMessage()."<br>"));
}
?>