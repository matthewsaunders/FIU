<%@ page language="java" contentType="text/html; charset=US-ASCII"
	pageEncoding="US-ASCII"%>
<%@page import="java.util.*"%>
<%@page import="account.modelstest.User"%>
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=US-ASCII">
<title>Insert title here</title>
<link rel="stylesheet" href="jquery-ui-1.10.2.custom/css/south-street/jquery-ui-1.10.2.custom.css" />
<link href="home.css" rel="stylesheet" type="text/css" />
<script src="jquery-ui-1.10.2.custom/js/jquery-1.9.1.js"></script>
<script src="jquery-ui-1.10.2.custom/js/jquery-ui-1.10.2.custom.js"></script>
<script>
	$(function() {
		$("#dialog").dialog({
			autoOpen : false,
			show : {
				effect : "fold",
				duration : 1000
			},
			hide : {
				effect : "fold",
				duration : 1000
			}
		});

		$("#opener").click(function() {
			$("#dialog").dialog("open");
		});
	});
</script>
</head>
<body>
	<div id="dialog" title="Choose User:">
		<form method="GET" action="AccountController">
			<ul style="list-style-type: none;">
				<%
					ArrayList<User> nonAdminList = null;
					nonAdminList = (ArrayList) request.getAttribute("nonAdmin");

					while (!nonAdminList.isEmpty()) {
						User user = nonAdminList.remove(0);

						out.println("<li ><input type=\"checkbox\" name=\"selection\" value=\""
								+ user.getUserName()
								+ "\"/>"
								+ user.getFname()
								+ " "
								+ user.getLname() + "</li>");
					}
				%>
			</ul>
			<input style="float: right;" class="admin-button" type="submit"
				name="submitAdmin" value="Submit" />
		</form>
	</div>

	<button id="opener">Open Dialog</button>
</body>
</html>