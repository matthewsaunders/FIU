package account.controllertest;

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

import account.modelstest.*;


/**
 * Servlet implementation class AccountController
 */
@WebServlet("/AccountController")
public class AccountController extends HttpServlet {
	private static final long serialVersionUID = 1L;
	private Registration reg;
	private getUserRow userRow;
	private LogInAndOut logInOut;
	private Comments comments;
	private getCommentsInfo commentsInfo;
	
	/**
	 * @see HttpServlet#HttpServlet()
	 */
	public AccountController() {
		super();
	}
	
	public void setRegistration(Registration stubRegistration){
		this.reg = stubRegistration;
	}
	
	public Registration getRegistration(){
		return this.reg;
	}
	
	public void setUserRow(getUserRow o){
		this.userRow = o;
	}
	
	public getUserRow getUserRow(){
		return userRow;
	}
	
	public void setLogInOut(LogInAndOut o){
		this.logInOut = o;
	}
	
	public LogInAndOut getLogInOut(){
		return logInOut;
	}
	
	public void setComments(Comments o){
		this.comments = o;
	}
	
	public Comments getComments(){
		return comments;
	}
	
	public void setCommentsInfo(getCommentsInfo o){
		this.commentsInfo = o;
	}
	
	public getCommentsInfo getCommentsInfo(){
		return commentsInfo;
	}

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse
	 *      response)
	 */
	protected void doGet(HttpServletRequest http_request,
			HttpServletResponse http_response) throws ServletException, IOException {
		// String forward = "/FamilyTree/"; // Used to redirect browser

		// Get a map of the request parameters
		@SuppressWarnings("unchecked")
		Map parameters = http_request.getParameterMap();

		// request from registration page
		if (parameters.containsKey("register")) {

			//Registration reg = new Registration();

			String fName = http_request.getParameter("first_name");
			String lName = http_request.getParameter("last_name");
			String email = http_request.getParameter("email");
			String pass = http_request.getParameter("password");

			if (reg.doRegistration(fName, lName, email, pass))
				http_response.sendRedirect("welcome.jsp");
			else {
				http_request.setAttribute("message",
						"Email already taken   \n Please use another email");
				http_request.getRequestDispatcher("registration.jsp").forward(
						http_request, http_response);
			}
		}

		// Request from login
		if (parameters.containsKey("login")) {

			// Setup response
			http_response.setContentType("text/html;charset=UTF-8");

			// Get values from JSP
			String username = http_request.getParameter("username");
			String password = http_request.getParameter("password");

			// doLogin
			HttpSession session = http_request.getSession(true);

			if (!username.equals("") && !password.equals("")
					&& logInOut.doLogin(username, password)) {
					//&& LogInAndOut.doLogin(username, password)) {

				// get complete name of user that log in
				//String[] row = getUserRow.getUserInfo(username);
				String[] row = userRow.getUserInfo(username);

				// get the whole list of comments
				//ArrayList<Comments> mylist = getCommentsInfo.getComments();
				ArrayList<Comments> mylist = commentsInfo.getComments();

				int total_comments = mylist.size();

				// Create unique session
				String sessionID = UUID.randomUUID().toString();
				session.setAttribute("username", username);
				session.setAttribute("sessionID", sessionID);
				session.setAttribute("fname", row[1]);
				session.setAttribute("lname", row[2]);
				session.setAttribute("privileges", row[3]);

				http_request.setAttribute("comments", mylist);
				http_request.setAttribute("total_comments", total_comments);

				// Redirect to landing page
				if (row[3].equals("s")) {
					ArrayList<User> nonAdmin = Administration.findNoAdmin();
					ArrayList<User> requests = Administration
							.showAdminRequest();
					http_request.setAttribute("nonAdmin", nonAdmin);
					http_request.setAttribute("requests", requests);
				} else {
					ArrayList<User> nonAdmin = new ArrayList<User>();
					ArrayList<User> requests = new ArrayList<User>();
					http_request.setAttribute("nonAdmin", nonAdmin);
					http_request.setAttribute("requests", requests);
				}
				http_request.getRequestDispatcher("home.jsp").forward(http_request,
						http_response);
			}
			// If either field was left empty
			else if (username.equals("") || password.equals("")) {
				http_request.setAttribute("message",
						"Please enter Email and Password");
				http_request.getRequestDispatcher("welcome.jsp").forward(http_request,
						http_response);
			}
			// Otherwise, username/password combination is incorrect
			else {
				http_request.setAttribute("message",
						"Invalid email/password combination"); // Will be
																// available as
																// ${message}
				http_request.getRequestDispatcher("welcome.jsp").forward(http_request,
						http_response);
			}
		}

		// Perform logout
		if (parameters.containsKey("logout")) {
			HttpSession session = http_request.getSession();
			session.invalidate();

			http_response.sendRedirect("welcome.jsp");
		}

		if (parameters.containsKey("reset")) {
			http_response.setContentType("text/html;charset=UTF-8");

			// Get values from JSP
			String email = http_request.getParameter("email");

			PasswordReset reset = new PasswordReset();

			if (reset.checkEmail(email)) {
				http_response.sendRedirect("welcome.jsp");
			} else {
				http_request.setAttribute("message",
						"Email entered is not registered \n Please try again");
				http_request.getRequestDispatcher("passwordReset.jsp").forward(
						http_request, http_response);
			}
		}

		if (parameters.containsKey("makeAdmin")) {
			ArrayList<User> nonAdmin = Administration.findNoAdmin();

			http_request.setAttribute("nonAdmin", nonAdmin);
			http_request.getRequestDispatcher("showNonAdmin.jsp").forward(http_request,
					http_response);

		}

		if (parameters.containsKey("submitAdmin")) {

			try {
				String[] selection = http_request.getParameterValues("selection");
				ArrayList<User> users = new ArrayList<User>();

				for (int i = 0; i < selection.length; i++) {
					User newUser = new User(null, null, null, null);
					newUser.setUserName(selection[i]);
					users.add(newUser);
				}

				Administration.makeAdmin(users);

				HttpSession session = http_request.getSession();

				// get the whole list of comments
				ArrayList<Comments> mylist = commentsInfo.getComments();
				int total_comments = mylist.size();

				http_request.setAttribute("comments", mylist);
				http_request.setAttribute("total_comments", total_comments);

				// Redirect to landing page
				if (session.getAttribute("privileges").toString().equals("s")) {
					ArrayList<User> nonAdmin = Administration.findNoAdmin();
					ArrayList<User> requests = Administration
							.showAdminRequest();
					http_request.setAttribute("nonAdmin", nonAdmin);
					http_request.setAttribute("requests", requests);
				} else {
					ArrayList<User> nonAdmin = new ArrayList<User>();
					ArrayList<User> requests = new ArrayList<User>();
					http_request.setAttribute("nonAdmin", nonAdmin);
					http_request.setAttribute("requests", requests);
				}
				http_request.getRequestDispatcher("home.jsp").forward(http_request,
						http_response);
			} catch (Exception e) {
				System.out.println("Nothing was selected");

				HttpSession session = http_request.getSession();

				// get the whole list of comments
				ArrayList<Comments> mylist = commentsInfo.getComments();
				int total_comments = mylist.size();

				http_request.setAttribute("comments", mylist);
				http_request.setAttribute("total_comments", total_comments);

				// Redirect to landing page
				if (session.getAttribute("privileges").toString().equals("s")) {
					ArrayList<User> nonAdmin = Administration.findNoAdmin();
					ArrayList<User> requests = Administration
							.showAdminRequest();
					http_request.setAttribute("nonAdmin", nonAdmin);
					http_request.setAttribute("requests", requests);
				} else {
					ArrayList<User> nonAdmin = new ArrayList<User>();
					ArrayList<User> requests = new ArrayList<User>();
					http_request.setAttribute("nonAdmin", nonAdmin);
					http_request.setAttribute("requests", requests);
				}
				http_request.getRequestDispatcher("home.jsp").forward(http_request,
						http_response);
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
			ArrayList<Comments> mylist = commentsInfo.getComments();
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
