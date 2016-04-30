<?php
print("<h2>Seed DB</h2>");

//connect to DB
include 'db/connectDatabase.php';

//Attempt to create DB tables
include 'db/createDbTables.php';

//Populate DB Tables
include 'db/seedUsers.php';
include 'db/seedCookbooks.php';
include 'db/seedRecipes.php';
include 'db/seedIngredients.php';
include 'db/seedContainsRecipe.php';
include 'db/seedContainsIngredient.php';

//Close PDO DB connection
print("<h2>FINISHED! Closing connection to DB</h2>");
$conn = null;
?>