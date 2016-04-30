<?php
/*
ID INT(11) AUTO_INCREMENT PRIMARY KEY,
name VARCHAR(150),
author VARCHAR(100) NOT NULL,
cooktime INT,
difficulty INT(5),
instructions TEXT
*/
/*
http://www.myrecipes.com/recipe/spinach-and-cheese-omelet
http://allrecipes.com/recipe/todds-famous-blueberry-pancakes/
http://www.cookingchanneltv.com/recipes/kelsey-nixon/chocolate-chip-cookies.html
http://www.foodnetwork.com/recipes/ellie-krieger/cumin-grilled-chicken-breasts-recipe.html
http://cooking.nytimes.com/recipes/1016231-pizza-margherita
*/

$table = "recipe";
print("<h4>Inserting records into $table</h4>");

try{
	$instructions = "1. Blend and Pour. Process eggs and 2 Tbsp. water in a blender until blended. Melt butter in an 8-inch nonstick skillet over medium heat; add spinach and tomatoes, and saut´´ 1 minute or until spinach is wilted. Add salt and egg mixture to skillet.
		2. Lift and Tilt. As egg mixture starts to cook, gently lift edges of omelet with a spatula, and tilt pan so uncooked egg mixture flows underneath, cooking until almost set (about 1 minute). Cover skillet, and cook 1 minute.
		3. Fold and Serve. Sprinkle omelet with cheese and pepper. Fold omelet in half, allowing cheese to melt. Slide cooked omelet onto a serving plate, and season with salt to taste. Serve with buttered toast and fresh fruit.
		";
	$sql = "INSERT INTO $table (id, name, author, cooktime, difficulty, instructions)
		VALUES(1, 'Omelette Du Fromage', 'Leo Martin', 20, 2, '$instructions');";
	$conn->exec($sql);
	print("....Inserted Record 1<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 1<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$instructions = "1.In a large bowl, sift together flour, salt, baking powder and sugar. In a small bowl, beat together egg and milk. Stir milk and egg into flour mixture. Mix in the butter and fold in the blueberries. Set aside for 1 hour.
		Heat a lightly oiled griddle or frying pan over medium high heat. Pour or scoop the batter onto the griddle, using approximately 1/4 cup for each pancake. Brown on both sides and serve hot.
		";
	$sql = "INSERT INTO $table (id, name, author, cooktime, difficulty, instructions)
		VALUES(2, 'Todd\'s Famous Blueberry Pancakes', 'Matthew Saunders', 75, 1, '$instructions');";
	$conn->exec($sql);
	print("....Inserted Record 2<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 2<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$instructions = "Preheat the oven to 350 degrees F. Line a baking sheet with parchment paper. 
		Cream together the butter and sugars in a mixing bowl, mixing until pale yellow and light and fluffy, about 3 minutes. Mix in the eggs one at a time, and then the vanilla until combined. 
		Whisk together the flour, baking powder, baking soda and salt in a separate mixing bowl. Slowly incorporate the dry ingredients into the wet ingredients. Stir in the chocolate chips. Portion 2 tablespoons of dough for each cookie and roll together to form a ball, spacing the dough balls 2 inches apart on the baking sheet. 
		Bake until the edges just start to brown, 12 to 14 minutes. Transfer to a wire rack to cool.
		";
	$sql = "INSERT INTO $table (id, name, author, cooktime, difficulty, instructions)
		VALUES(3, 'Chocolate Chip Cookies', 'John Doe', 45, 1, '$instructions');";
	$conn->exec($sql);
	print("....Inserted Record 3<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 3<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$instructions = "
		Place a pizza stone or tiles on the middle rack of your oven and turn heat to its highest setting. Let it heat for at least an hour.
		Put the sauce in the center of the stretched dough and use the back of a spoon to spread it evenly across the surface, stopping approximately 1/2 inch from the edges.
		Drizzle a little olive oil over the pie. Break the cheese into large pieces and place these gently on the sauce. Scatter basil leaves over the top.
		Using a pizza peel, pick up the pie and slide it onto the heated stone or tiles in the oven. Bake until the crust is golden brown and the cheese is bubbling, approximately 4 to 8 minutes.
		In a food processor, whiz together whole, drained canned tomatoes, a splash of olive oil and a sprinkle of salt. Keep leftover sauce refrigerated.
		";
	$sql = "INSERT INTO $table (id, name, author, cooktime, difficulty, instructions)
		VALUES(4, 'Pizza Margherita', 'Jane Doe', 90, 5, '$instructions');";
	$conn->exec($sql);
	print("....Inserted Record 4<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 4<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

try{
	$instructions = "Spray a grill or grill pan with cooking spray and heat to medium-high heat. Rub chicken breasts with olive oil. Combine cumin, salt and pepper and rub spice mixture evenly onto chicken breasts. Grill until grill marks have formed and chicken is cooked through, about 4-5 minutes per side. Remove from heat, let rest for 5 minutes, then slice into 1/2-inch thick slices. Serve over coleslaw, if desired.
		";
	$sql = "INSERT INTO $table (id, name, author, cooktime, difficulty, instructions)
		VALUES(5, 'Cumin Grilled Chicken Breasts', 'Jane Doe', 25, 3, '$instructions');";
	$conn->exec($sql);
	print("....Inserted Record 5<br>");
} catch (PDOException $e){
	print("....ERROR: unable to insert record 5<br>");
	//print("    ".print($e->getMessage()."<br>"));
}

?>