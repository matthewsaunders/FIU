<?php
/*
cookbookId INT(11),
recipeId INT(11),
PRIMARY KEY(cookbookId, recipeId)
*/

$table = "containsRecipe";
print("<h4>Inserting records into $table</h4>");

try{
	$sql = "INSERT INTO $table (cookbookId, recipeId)
		VALUES(1, 1);";
	$conn->exec($sql);
	print("....Inserted Record 1<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 1<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (cookbookId, recipeId)
		VALUES(1, 2);";
	$conn->exec($sql);
	print("....Inserted Record 2<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 2<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (cookbookId, recipeId)
		VALUES(2, 4);";
	$conn->exec($sql);
	print("....Inserted Record 3<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 3<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (cookbookId, recipeId)
		VALUES(2, 5);";
	$conn->exec($sql);
	print("....Inserted Record 4<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 4<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (cookbookId, recipeId)
		VALUES(3, 5);";
	$conn->exec($sql);
	print("....Inserted Record 5<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 5<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (cookbookId, recipeId)
		VALUES(4, 4);";
	$conn->exec($sql);
	print("....Inserted Record 6<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 6<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (cookbookId, recipeId)
		VALUES(5, 3);";
	$conn->exec($sql);
	print("....Inserted Record 7<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 7<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (cookbookId, recipeId)
		VALUES(3, 4);";
	$conn->exec($sql);
	print("....Inserted Record 8<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 8<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (cookbookId, recipeId)
		VALUES(6, 4);";
	$conn->exec($sql);
	print("....Inserted Record 9<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 9<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (cookbookId, recipeId)
		VALUES(6, 5);";
	$conn->exec($sql);
	print("....Inserted Record 10<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 10<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (cookbookId, recipeId)
		VALUES(6, 3);";
	$conn->exec($sql);
	print("....Inserted Record 11<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 11<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (cookbookId, recipeId)
		VALUES(7, 4);";
	$conn->exec($sql);
	print("....Inserted Record 12<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 12<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (cookbookId, recipeId)
		VALUES(8, 1);";
	$conn->exec($sql);
	print("....Inserted Record 13<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 13<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$sql = "INSERT INTO $table (cookbookId, recipeId)
		VALUES(8, 2);";
	$conn->exec($sql);
	print("....Inserted Record 14<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 14<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

?>