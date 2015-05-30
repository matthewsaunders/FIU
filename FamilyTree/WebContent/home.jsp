<%@ page language="java" contentType="text/html; charset=US-ASCII"
	pageEncoding="US-ASCII"%>
<%@page import="java.util.*"%>
<%@page import="account.models.Comments"%>
<%@page import="account.models.User"%>
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>My Family Tree</title>
<meta name="keywords" content="" />
<meta name="description" content="" />
<script src="//ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js"></script>
<script src="jquery-ui-1.10.2.custom/js/jquery-1.9.1.js"></script>
<script src="jquery-ui-1.10.2.custom/js/jquery-ui-1.10.2.custom.js"></script>
<link
	href="http://fonts.googleapis.com/css?family=Open+Sans:400,300,600,700|Archivo+Narrow:400,700"
	rel="stylesheet" type="text/css">
<link href="home.css" rel="stylesheet" type="text/css" media="all" />
<link rel="shortcut icon" href="images/favicon.ico">
<link rel="stylesheet"
	href="jquery-ui-1.10.2.custom/css/south-street/jquery-ui-1.10.2.custom.css" />

<%
	if (session.getAttribute("sessionID") == null)
		response.sendRedirect("welcome.jsp");
	else {
%>

<script type="text/javascript">
	var total_comments = "<%=request.getAttribute("total_comments")%>";
	$(document).ready(function() {		
		setInterval(function() {
	        $.ajax({
	            type: "GET",
	            data: "total_comments=" + total_comments + "&type=getnewcomment",
	            url: "CommentServlet",
	            success: function(html) {
	            	if(html != ""){
	            		var obj = $.parseJSON(html);
	            		total_comments = parseInt(total_comments) + parseInt(obj[0].total);
	            		length = obj.length;
	            		for (var i = length-1; i >= 0 ; i--) {
	            			// IF PARENT
		            		if(parseInt(obj[i].parent) == 0){
		            			//alert("New comment from: " + obj[i].first + " " + obj[i].last);
		            			$("#thought").after(
											'<div class="originalpost-' + obj[i].id + '"><br/><hr><fieldset><legend><h2>'+ obj[i].first + " " + obj[i].last +'</h2></legend><p>'
													+ obj[i].text
													+ '</p><div class="replays-' + obj[i].id + '" style="margin-left: 20px;"><input type="text" id="replaycomment-' + obj[i].id + '" name="replaycomment" value=""><button type="button" class="button" onclick="makeReplay(this);">Post</button></div></fieldset></div>');
							
		            		
		            		}else{// IF CHILD
		            			//alert("New comment from: " + obj[i].first + " " + obj[i].last);
			            		$('#replaycomment-' + obj[i].parent).before(
			        					'<h3>' + obj[i].first + " " + obj[i].last + '</h3><p>' + obj[i].text + '</p>');
			        			$('#replaycomment-' + obj[i].parent).val("");
		            		}
	            		}
	            	}
	       		}
	        });
	    }, 5000);
		
		$("#notificationDiv").hide();
	});
	
	function requestAdmin() {
		
		$.ajax({
			type : "POST",
			url : "AccountController",
			data : "type=adminRequest",
			success : function(result) {
				alert(result);
			}
		});
	}

	function linkUser() {
			
		var dob = $('#dateofbirth').val();
		$.ajax({
			type : "POST",
			url : "AccountController",
			data : "type=link"+"&dob=" + dob,
			success : function(result) {
				alert("The link to your page is: " + result);
			}
		});
		$("#link").dialog("close");
	}
	function removeText() {
		if ($("#comment").val() == "Write here what are you thinking...") {
			$("#comment").val("");
			$("#comment").removeAttr("style");
		}
	}

	function makePost() {
		$(".content").fadeOut(1000,function() {
			if ($("#comment").val() == "")return;
				var text = $("#comment").val();
				// do the ajax call to insert the comment and refresh the content area
				// return the id from the ajax call
				$.ajax({  
				    type: "GET",  
				    url: "CommentServlet",  
				    data: "text="+text+"&type=comment",
				    success: function(result){
				    	var id = result;
				    	var user = "<%=session.getAttribute("fname")%> <%=session.getAttribute("lname")%>";
						$("#thought")
								.after(
										'<div class="originalpost-' + id + '"><br/><hr><fieldset><legend><h2>'+user+'</h2></legend><p>'
												+ text
												+ '</p><div class="replays-' + id + '" style="margin-left: 20px;"><input type="text" id="replaycomment-' + id + '" name="replaycomment" value=""><button type="button" class="button" onclick="makeReplay(this);">Post</button></div></fieldset></div>');
						$(".content").fadeIn(1000);
						$("#comment").val("");
						total_comments = parseInt(total_comments) + 1;
			    	}                
			  	});
			}
		);
	}

	function makeReplay(elem) {
		var father = $(elem).parent().attr("class");
		var id = father.split("-")[1];
		var text = $('#replaycomment-' + id).val();
		if (text) {
			var user = "<%=session.getAttribute("fname")%> <%=session.getAttribute("lname")%>";
			$('#replaycomment-' + id).before(
					'<h3>' + user + '</h3><p>' + text + '</p>');
			$('#replaycomment-' + id).val("");

			//do ajax call to insert the coment without notifiying the user
			  $.ajax({  
				    type: "GET",  
				    url: "CommentServlet",  
				    data: "id="+id+"&text="+text+"&type=reply",
				    success: function(result){
				    	total_comments = parseInt(total_comments) + 1;
			    	}                
			  });
		}	
	}

	function showNotifications() {
		$(".content").fadeOut(1000, function() {
			$("#notificationDiv").show();
			$("#notificationDiv").attr("class", "notificationDIV");
		});
	}

	function makeAdmin() {
		$("#dialog").dialog("open");
	}

	function submitRequest() {
		$("#requests").dialog("open");
	}
	
	function doLink() {
		$("#link").dialog("open");
	}
	
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
	
	$(function() {
		$("#requests").dialog({
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

		$("#requestOpener").click(function() {
			$("#requests").dialog("open");
		});
	});
	
	$(function() {
		$("#link").dialog({
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

		$("#openLink").click(function() {
			$("#link").dialog("open");
		});
	});
</script>
</head>

<body>
	<div class="header">
		<div class="logo">
			<img id="logoPic"
				src="images/logo.png">
		</div>
		<ul>
			<li><a href="#"> Request </a>
				<ul
					<%String privileges = session.getAttribute("privileges")
						.toString();
				if (!privileges.equalsIgnoreCase("u")) {%>
					style="margin-left: -60px !important;" <%}%>>
					<li><a style="cursor: pointer;" onclick="doLink()"> Family Link </a></li>
					<%
						if (privileges.equalsIgnoreCase("u")) {
					%>
					<li><a style="cursor: pointer;" onclick="requestAdmin()">Administrative Rights</a></li>
					<%
						}
					%>
				</ul></li>
			<li style="margin-left: 40px;">
				<form method="GET" action="AccountController">
					<label> <input class="logout" type="submit" name="logout"
						value="Logout">
					</label>
				</form>
			</li>
		</ul>
	</div>

	<div class="left-sidebar">
		<div class="username">
			<h2 style="font-style: oblique;">Welcome:</h2>
			<h1 style="font-style: oblique;"><%=session.getAttribute("fname")%>
				<%=session.getAttribute("lname")%></h1>
			<%
				if (privileges.equalsIgnoreCase("s")) {
			%>
			<ul class="notifications" onclick="submitRequest()" id="requestOpener">
				<li><a href="#">Notifications</a></li>
			</ul>
			<ul class="notifications" onclick="makeAdmin()" id="opener">
				<li><a href="#">Make Administrator</a></li>
			</ul>
			<%
				}
			%>
		</div>
	</div>

	<div class="content" style="margin-left: 100px;">
		<div id="thought" style="padding-bottom: 20px;">
			<textarea name="comment" id="comment" class="comment"
				placeholder="Write your comment here..."></textarea>
			<button type="button" class="button" onclick="makePost();">Post</button>
		</div>

		<%
			ArrayList<Comments> comment = null;
				comment = (ArrayList) request.getAttribute("comments");

				while (comment.size() != 0) {
					Comments mycomment = comment.remove(0);
					int id = mycomment.getID();
		%>
		<div class="originalpost-<%=id%>">
			<br />
			<hr>
			<fieldset
				style="width: auto; padding-left: 20px; padding-right: 30px;">
				<legend>
					<h2><%=mycomment.getFname()%>
						<%=mycomment.getLname()%></h2>
				</legend>
				<p><%=mycomment.getText()%></p>
				<div class="replays-<%=id%>" style="margin-left: 20px;">
					<%
						while (comment.size() != 0) {
									if (comment.get(0).getParent() != 0) {
										mycomment = comment.remove(0);
					%>
					<h3><%=mycomment.getFname()%>
						<%=mycomment.getLname()%></h3>
					<p><%=mycomment.getText()%></p>
					<%
						} else {
										break;
									}
					%>
					<%
						}
					%>
					<input type="text" id="replaycomment-<%=id%>" name="replaycomment"
						value="" placeholder="Reply here...">
					<button type="button" class="button" onclick="makeReplay(this);">Post</button>
				</div>
			</fieldset>
		</div>
 <%
				}
 %>
	</div>

	<div id="notificationDiv">
		<p>Estas son las notificationes so far...</p>
	</div>

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
	<div id="requests" title="Pending Requests:">
		<form method="POST" action="AccountController">
			<ul style="list-style-type: none;">
				<%
					ArrayList<User> requests = null;
					requests = (ArrayList) request.getAttribute("requests");
					int i = 1;

					if(requests.isEmpty())
						out.println("<p>No pending requests</p>");
					else {
						while (!requests.isEmpty()) {
							User user = requests.remove(0);
	
							out.println("<li>" + user.getFname() + " " + user.getLname() + "<br/>"
									+ "<input style=\"padding-bottom= 10px;\" type=\"radio\" name=\"decision" + i + "\" value=\"approve\">Approve</inpunt>"
									+ "<input style=\"padding-bottom= 10px;\" type=\"radio\" name=\"decision" + i + "\" value=\"deny\">Deny</inpunt>"
									+ "</li><br/>" 
									+ "<input type=\"hidden\" name=\"username" + i + "\" value=" + user.getUserName() + " />");
							i++;
						}
					}
					
				%>
			</ul>
			<input type="hidden" name="totalRequest" id="totalRequest" value="<%=i-1%>" />
			<input style="float: right;" class="admin-button" type="submit"
				name="requestSubmit" value="Submit" />
		</form>
	</div>
	<div id="link" title="Enter Date of Birth:">
		<form>
			<input style="margin-top: 10px; margin-bottom: 10px;" type="date" id="dateofbirth"/>
			<button class="admin-button" style="float: right;" type="button" class="button" onclick="linkUser();">Link Me</button>
		</form>
	</div>
	<%
		}
	%>
</body>
</html>
