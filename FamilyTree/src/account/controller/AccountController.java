package account.controller;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Map;
import java.util.UUID;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import account.models.Administration;
import account.models.Comments;
import account.models.Link;
import account.models.LogInAndOut;
import account.models.PasswordReset;
import account.models.Registration;
import account.models.User;
import account.models.getCommentsInfo;
import account.models.getUserRow;

/**
 * Servlet implementation class AccountController
 */
@WebServlet("/AccountController")
public class AccountController extends HttpServlet {
	private static final long serialVersionUID = 1L;

	/**
	 * @see HttpServlet#HttpServlet()
	 */
	public AccountController() {
		super();
	}

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse
	 *      response)
	 */
	protected void doGet(HttpServletRequest request,
			HttpServletResponse response) throws ServletException, IOException {
		// String forward = "/FamilyTree/"; // Used to redirect browser

		// Get a map of the request parameters
		@SuppressWarnings("unchecked")
		Map parameters = request.getParameterMap();

		// request from registration page
		if (parameters.containsKey("register")) {

			Registration reg = new Registration();

			String fName = request.getParameter("first_name");
			String lName = request.getParameter("last_name");
			String email = request.getParameter("email");
			String pass = request.getParameter("password");

			if (reg.doRegistration(fName, lName, email, pass))
				response.sendRedirect("welcome.jsp");
			else {
				request.setAttribute("message",
						"Email already taken   \n Please use another email");
				request.getRequestDispatcher("registration.jsp").forward(
						request, response);
			}
		}

		// Request from login
		if (parameters.containsKey("login")) {

			// Setup response
			response.setContentType("text/html;charset=UTF-8");

			// Get values from JSP
			String username = request.getParameter("username");
			String password = request.getParameter("password");

			// doLogin
			HttpSession session = request.getSession(true);

			if (!username.equals("") && !password.equals("")
					&& LogInAndOut.doLogin(username, password)) {

				// get complete name of user that log in
				String[] row = getUserRow.getUserInfo(username);

				// get the whole list of comments
				ArrayList<Comments> mylist = getCommentsInfo.getComments();

				int total_comments = mylist.size();

				// Create unique session
				String sessionID = UUID.randomUUID().toString();
				session.setAttribute("username", username);
				session.setAttribute("sessionID", sessionID);
				session.setAttribute("fname", row[1]);
				session.setAttribute("lname", row[2]);
				session.setAttribute("privileges", row[3]);

				request.setAttribute("comments", mylist);
				request.setAttribute("total_comments", total_comments);

				// Redirect to landing page
				if (row[3].equals("s")) {
					ArrayList<User> nonAdmin = Administration.findNoAdmin();
					ArrayList<User> requests = Administration
							.showAdminRequest();
					request.setAttribute("nonAdmin", nonAdmin);
					request.setAttribute("requests", requests);
				} else {
					ArrayList<User> nonAdmin = new ArrayList<User>();
					ArrayList<User> requests = new ArrayList<User>();
					request.setAttribute("nonAdmin", nonAdmin);
					request.setAttribute("requests", requests);
				}
				request.getRequestDispatcher("home.jsp").forward(request,
						response);
			}
			// If either field was left empty
			else if (username.equals("") || password.equals("")) {
				request.setAttribute("message",
						"Please enter Email and Password");
				request.getRequestDispatcher("welcome.jsp").forward(request,
						response);
			}
			// Otherwise, username/password combination is incorrect
			else {
				request.setAttribute("message",
						"Invalid email/password combination"); // Will be
																// available as
																// ${message}
				request.getRequestDispatcher("welcome.jsp").forward(request,
						response);
			}
		}

		// Perform logout
		if (parameters.containsKey("logout")) {
			HttpSession session = request.getSession();
			session.invalidate();

			response.sendRedirect("welcome.jsp");
		}

		if (parameters.containsKey("reset")) {
			response.setContentType("text/html;charset=UTF-8");

			// Get values from JSP
			String email = request.getParameter("email");

			PasswordReset reset = new PasswordReset();

			if (reset.checkEmail(email)) {
				response.sendRedirect("welcome.jsp");
			} else {
				request.setAttribute("message",
						"Email entered is not registered \n Please try again");
				request.getRequestDispatcher("passwordReset.jsp").forward(
						request, response);
			}
		}

		if (parameters.containsKey("makeAdmin")) {
			ArrayList<User> nonAdmin = Administration.findNoAdmin();

			request.setAttribute("nonAdmin", nonAdmin);
			request.getRequestDispatcher("showNonAdmin.jsp").forward(request,
					response);

		}

		if (parameters.containsKey("submitAdmin")) {

			try {
				String[] selection = request.getParameterValues("selection");
				ArrayList<User> users = new ArrayList<User>();

				for (int i = 0; i < selection.length; i++) {
					User newUser = new User(null, null, null, null);
					newUser.setUserName(selection[i]);
					users.add(newUser);
				}

				Administration.makeAdmin(users);

				HttpSession session = request.getSession();

				// get the whole list of comments
				ArrayList<Comments> mylist = getCommentsInfo.getComments();
				int total_comments = mylist.size();

				request.setAttribute("comments", mylist);
				request.setAttribute("total_comments", total_comments);

				// Redirect to landing page
				if (session.getAttribute("privileges").toString().equals("s")) {
					ArrayList<User> nonAdmin = Administration.findNoAdmin();
					ArrayList<User> requests = Administration
							.showAdminRequest();
					request.setAttribute("nonAdmin", nonAdmin);
					request.setAttribute("requests", requests);
				} else {
					ArrayList<User> nonAdmin = new ArrayList<User>();
					ArrayList<User> requests = new ArrayList<User>();
					request.setAttribute("nonAdmin", nonAdmin);
					request.setAttribute("requests", requests);
				}
				request.getRequestDispatcher("home.jsp").forward(request,
						response);
			} catch (Exception e) {
				System.out.println("Nothing was selected");

				HttpSession session = request.getSession();

				// get the whole list of comments
				ArrayList<Comments> mylist = getCommentsInfo.getComments();
				int total_comments = mylist.size();

				request.setAttribute("comments", mylist);
				request.setAttribute("total_comments", total_comments);

				// Redirect to landing page
				if (session.getAttribute("privileges").toString().equals("s")) {
					ArrayList<User> nonAdmin = Administration.findNoAdmin();
					ArrayList<User> requests = Administration
							.showAdminRequest();
					request.setAttribute("nonAdmin", nonAdmin);
					request.setAttribute("requests", requests);
				} else {
					ArrayList<User> nonAdmin = new ArrayList<User>();
					ArrayList<User> requests = new ArrayList<User>();
					request.setAttribute("nonAdmin", nonAdmin);
					request.setAttribute("requests", requests);
				}
				request.getRequestDispatcher("home.jsp").forward(request,
						response);
			}
		}

	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse
	 *      response)
	 */
	protected void doPost(HttpServletRequest request,
			HttpServletResponse response) throws ServletException, IOException {

		HttpSession session = request.getSession();

		// Get a map of the request parameters
		@SuppressWarnings("unchecked")
		Map parameters = request.getParameterMap();

		if (parameters.containsKey("requestSubmit")) {

			int i = Integer.parseInt(request.getParameter("totalRequest"));
			String option = "";
			String username = "";
			ArrayList<User> approved = new ArrayList<User>();
			ArrayList<User> denied = new ArrayList<User>();
			
			while(i>0) {
				User newUser = new User(null, null, null, null);
				option = request.getParameter("decision" + i);
				username = request.getParameter("username" + i);
				
				if(option.equals("approve")) {
					newUser.setUserName(username);
					approved.add(newUser);
				} else {
					newUser.setUserName(username);
					denied.add(newUser);
				}
				i--;
			}

			Administration.makeAdmin(approved);
			Administration.dropFromTable(approved);
			Administration.dropFromTable(denied);
			
			// get the whole list of comments
			ArrayList<Comments> mylist = getCommentsInfo.getComments();
			int total_comments = mylist.size();

			request.setAttribute("comments", mylist);
			request.setAttribute("total_comments", total_comments);

			// Redirect to landing page
			if (session.getAttribute("privileges").toString().equals("s")) {
				ArrayList<User> nonAdmin = Administration.findNoAdmin();
				ArrayList<User> requests = Administration.showAdminRequest();
				request.setAttribute("nonAdmin", nonAdmin);
				request.setAttribute("requests", requests);
			} else {
				ArrayList<User> nonAdmin = new ArrayList<User>();
				ArrayList<User> requests = new ArrayList<User>();
				request.setAttribute("nonAdmin", nonAdmin);
				request.setAttribute("requests", requests);
			}
			request.getRequestDispatcher("home.jsp").forward(request, response);
		} 
		//request is coming from non-admin page
		else {
			if (request.getParameter("type").equalsIgnoreCase("adminRequest")) {

				String username = session.getAttribute("username").toString();
				String fname = session.getAttribute("fname").toString();
				String lname = session.getAttribute("lname").toString();

				String result = Administration.sendRequest(username, fname,
						lname);
				response.getWriter().write(result);
			}
			if (request.getParameter("type").equalsIgnoreCase("link")) {
			
				String date = request.getParameter("dob");
				int result = Link.getMemberID(session.getAttribute("fname").toString(),
						session.getAttribute("lname").toString(), date);
				
				response.getWriter().write("Features/" + String.valueOf(result));
			}
		}

	}
}
