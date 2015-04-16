<?php
/*
recipeId INT(11),
ingredientName VARCHAR(150),
amount INT NOT NULL,
PRIMARY KEY(recipeId,ingredientName)
*/

$table = "containsIngredient";
print("<h4>Inserting records into $table</h4>");

//omlette
try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(1, 'eggs', '2');";
	$conn->exec($sql);
	print("....Inserted Record 1<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 1<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(1, 'butter', '1');";
	$conn->exec($sql);
	print("....Inserted Record 2<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 2<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(1, 'spinach', '1');";
	$conn->exec($sql);
	print("....Inserted Record 3<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 3<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(1, 'chopped tomatoes', '1/3');";
	$conn->exec($sql);
	print("....Inserted Record 4<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 4<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(1, 'salt', '1/8');";
	$conn->exec($sql);
	print("....Inserted Record 5<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 5<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(1, 'shredded swiss cheese', '1/3');";
	$conn->exec($sql);
	print("....Inserted Record 6<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 6<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (recipeId, ingredientName, amount)
		VALUES(1, 'pepper', '1/8');";
	$conn->exec($sql);
	print("....Inserted Record 7<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 7<br>");
	//print("    ".print($e->getMessage()."<br>"));
}



















































?>