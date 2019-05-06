#include "../utils/utilities.hpp"
#include "server.hpp"
#include <iostream>
#include "jeekjeek/interface.hpp"
#include "jeekjeek/exception.hpp"
#include "jeekjeek/user.hpp"
#include <string>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <string>
using namespace std;

class Session_id
{
	public:
		Session_id(string _display_name,string _username,string _pass,string _session_id)
		{
			display_name = _display_name;
			username = _username;
			password = _pass;
			session_id = _session_id;
		}
		string display_name;
		string username;
		string password;
		string session_id;
};

class Online_users
{
public:
	vector<Session_id> users;
};

int make_random_id(Online_users* online_users)
{
  int id = 0;
  bool duplicate = 1;
  while(duplicate)
  {
    duplicate = 0;
    srand(time(NULL));
    id = rand();
    for(int i = 0;i < int((online_users->users).size()); i++)
    {
      if((online_users->users)[i].session_id == to_string(id))
      {
        duplicate = 1;
        break;
      }
    }
  }
  return id;
}

class ShowPage : public RequestHandler {
	string filePath;

	public:
	ShowPage(string _filePath) { filePath = _filePath; }
	Response *callback(Request *req) {
		Response *res = new Response;
		res->setHeader("Content-Type", "text/html");
		string body = readFile(filePath.c_str());
		res->setBody(readFile(filePath.c_str()));
		return res;
	}
};

class ShowImage : public RequestHandler {
	string filePath;
	public:
	ShowImage(string _filePath) { filePath = _filePath; }
	Response *callback(Request *req) {
		Response *res = new Response;
		res->setHeader("Content-Type", "image/png");
		string body = readFile(filePath.c_str());
		res->setBody(body);
		return res;
	}
};

class LoginHandler : public RequestHandler {
	private:
		Interface* interface;
		Online_users* online_users;
	public:
		LoginHandler(Interface* _interface, Online_users* _online_users)
		{
			interface = _interface;
			online_users = _online_users;
		}
		Response *callback(Request *req)
		{
			Response *res = new Response;
			try
			{
				string username = req->getBodyParam("username");
				string pass = req->getBodyParam("pass");
				string display_name = "";
				cout << "Received Data: " << username << " - " << pass << endl;
				res->setHeader("Content-Type", "text/html");
				string info = username + " " + pass;
				interface->log_in(info);
				display_name = (interface->logedin_user)->get_name();
				res->setBody(readFile("htmlFiles/jeekjeek.html"));
				string id = req->getSessionId();
				bool loged = 0;
				for(int i = 0;i < int((online_users->users).size()); i++)
				{
					if((online_users->users)[i].session_id == id)
						loged = 1;
				}
				if(!loged)
				{
					int id;
          id = make_random_id(online_users);
					string session_id = to_string(id);
					Session_id new_session(display_name, username, pass, session_id);
					res->setSessionId(session_id);
					(online_users->users).push_back(new_session);
				}
			}
			catch ( Exception* exception)
			{
				res->setBody(readFile("htmlFiles/home.html"));
				exception->what();
			}
			interface->log_out("");
			return res;
		}
};

class Jeekjeek_handler : public RequestHandler {
	private:
		Interface* interface;
		Online_users* online_users;
	public:
		Jeekjeek_handler(Interface* _interface, Online_users* _online_users)
		{
			interface = _interface;
			online_users = _online_users;
		}
		Response *callback(Request *req)
		{
			bool loged_in = 0;
			Response *res = new Response;
			res->setHeader("Content-Type", "text/html");
			try
			{
				string id = req->getSessionId();
				for(int i = 0;i < int((online_users->users).size()); i++)
				{
					if((online_users->users)[i].session_id == id)
					{
						loged_in = 1;
						interface->log_out("");
						interface->log_in((online_users->users)[i].username + " " + (online_users->users)[i].password);
					}
				}
				if(!loged_in)
				{
					res->setBody("<script>window.location.href = \"/login_page\" </script>");
					return res;
				}
				string search_text = req->getBodyParam("search_text");
				cout << "Received Data: " << search_text << endl;
				string search_info = search_text;
				vector<string> jeeks = interface->search(search_info);

				string all = "";

				for(int i = 0;i < int(jeeks.size()); i++)
				{
					string jeek_id  = jeeks[i].substr(0,2);
					string body = readFile("htmlFiles/body.html");
					string Button = readFile("htmlFiles/container.html");
					int pos = Button.find("$");
					Button.replace(pos, 1, jeek_id);
					pos = Button.find("!!");
					Button.replace(pos, 2, jeeks[i]);
					pos = body.find("#$");
					body.replace(pos, 2, jeek_id);
					pos = body.find("!");
					body.replace(pos, 1, interface->show_jeek(jeek_id));
					pos = body.find("$$");
					body.replace(pos, 2, jeek_id);
					pos = body.find("@@");
					body.replace(pos, 2, jeek_id);
					pos = body.find("##");
					body.replace(pos, 2, jeek_id);
					pos = body.find("MM");
					string image_id = "I" + jeek_id;
					body.replace(pos, 2, image_id);
					string comment_id = "C" + jeek_id;
					pos = body.find("II");
					body.replace(pos, 2, comment_id);
					pos = body.find("CC");
					body.replace(pos, 2, comment_id);
					if(interface->is_liked_by_user(jeek_id))
					{
						pos = body.find("ZZZ");
						body.replace(pos, 3, "checked");
						pos = body.find("/dislike_icon");
						body.replace(pos, 13, "/like_icon");
					}
					all += "</br>";
					all += (Button + body);
				}
				res->setBody(all);
			}
			catch ( Exception* exception)
			{
				exception->what();
        res->setBody("<script>window.location.href = \"/jeekjeek\" </script>");
			}
			interface->log_out("");
			return res;
		}
};

class signup_handler : public RequestHandler {
	private:
		Interface* interface;
		Online_users* online_users;
	public:
		signup_handler(Interface* _interface, Online_users* _online_users)
		{
			interface = _interface;
			online_users = _online_users;
		}
		Response *callback(Request *req)
		{
			Response *res = new Response;
			try
			{
				string username = req->getBodyParam("username");
				string pass = req->getBodyParam("pass");
				string name = req->getBodyParam("name");
				string all = username + " " + name + " " + pass;
				cout << "Received Data: " << username << " - " << pass << endl;
				res->setHeader("Content-Type", "text/html");
				res->setBody(readFile("htmlFiles/login.html"));
				interface->sign_up(all);
			}
			catch ( Exception* exception)
			{
				res->setBody(readFile("htmlFiles/signup.html"));
				exception->what();
			}
			return res;
		}
};

class Get_username : public RequestHandler {
private:
	Online_users* online_users;
	public:
		Get_username(Online_users* _online_users)
		{
			online_users = _online_users;
		}
		string username = "";
		Response *callback(Request *req)
		{
			bool loged = 0;
			Response *res = new Response;
			try
			{
				string id = req->getSessionId();
				for(int i = 0;i < int((online_users->users).size()); i++)
				{
					if((online_users->users)[i].session_id == id)
					{
						loged = 1;
						username = (online_users->users)[i].username;
						res->setBody(username);
					}
				}
				if(!loged)
				{
					res->setBody("ERROR");
				}
				cout << "Received Data: " << username << endl;
				res->setHeader("Content-Type", "text/html");
			}
			catch (...)
			{
				res->setBody(readFile("htmlFiles/home.html"));
			}
			return res;
		}
};




class Get_name : public RequestHandler {
private:
	Online_users* online_users;
	public:
		Get_name(Online_users* _online_users)
		{
			online_users = _online_users;
		}
		string name = "";
		Response *callback(Request *req)
		{
			bool loged = 0;
			Response *res = new Response;
			try
			{
				string id = req->getSessionId();
				for(int i = 0;i < int((online_users->users).size()); i++)
				{
					if((online_users->users)[i].session_id == id)
					{
						loged = 1;
						name = (online_users->users)[i].display_name;
					}
					if(!loged)
					{
						res->setBody("ERROR");
					}
				}
				cout << "Received Data: " << name << endl;
				res->setHeader("Content-Type", "text/html");
				res->setBody(name);
			}
			catch (...)
			{
				res->setBody(readFile("htmlFiles/home.html"));
			}
			return res;
		}
};



class Logout_handler : public RequestHandler {
private:
	Online_users* online_users;
	public:
		Logout_handler(Online_users* _online_users)
		{
			online_users = _online_users;
		}
		string username = "";
		Response *callback(Request *req)
		{
			Response *res = new Response;
			try
			{
				string id = req->getSessionId();
				res->setSessionId("");
				for(int i = 0;i < int((online_users->users).size()); i++)
				{
					if((online_users->users)[i].session_id == id)
					{
						(online_users->users).erase((online_users->users).begin() + i);
					}
				}
				res->setHeader("Content-Type", "text/html");
				res->setBody(readFile("htmlFiles/login.html"));
			}
			catch (...)
			{
				res->setBody(readFile("htmlFiles/home.html"));
			}
			return res;
		}
};



class Rejeek_handler : public RequestHandler {
	private:
		Interface* interface;
		Online_users* online_users;
	public:
		Rejeek_handler(Interface* _interface, Online_users* _online_users)
		{
			interface = _interface;
			online_users = _online_users;
		}
		Response *callback(Request *req)
		{
			bool loged = 0;
			Response *res = new Response;
			try
			{
				string jeek_id = req->getBodyParam("jeek_id");
				cout << "jeek id : " << jeek_id << endl;
				string id = req->getSessionId();
				for(int i = 0;i < int((online_users->users).size()); i++)
				{
					if((online_users->users)[i].session_id == id)
					{
						interface->log_in((online_users->users)[i].username + " " + (online_users->users)[i].password);
						loged = 1;
					}
				}
				if(!loged)
					return res;
				else
				{
					interface->rejeek(jeek_id);
				}
				res->setHeader("Content-Type", "text/html");
			}
			catch (Exception* exception)
			{
        exception->what();
				res->setBody("<script>window.location.href = \"/jeekjeek\" </script>");
			}
			interface->log_out("");
			return res;
		}
};


class Like_handler : public RequestHandler {
	private:
		Interface* interface;
		Online_users* online_users;
	public:
		Like_handler(Interface* _interface, Online_users* _online_users)
		{
			interface = _interface;
			online_users = _online_users;
		}
		Response *callback(Request *req)
		{
			Response *res = new Response;
			try
			{
				string jeek_id = req->getBodyParam("jeek_id");
				string status = req->getBodyParam("status");
				string id = req->getSessionId();
				for(int i = 0;i < int((online_users->users).size()); i++)
				{
					if((online_users->users)[i].session_id == id)
					{
						interface->log_in((online_users->users)[i].username + " " + (online_users->users)[i].password);
						if(status == "true")
						{
							interface->like(jeek_id);
						}
						else
						{
							interface->dislike(jeek_id);
						}
					}
				}
				res->setHeader("Content-Type", "text/html");
			}
			catch(Exception* exc)
			{
				exc->what();
			}
			interface->log_out("");
			return res;
		}
};

class Notifications_handler : public RequestHandler {
	private:
		Interface* interface;
		Online_users* online_users;
	public:
		Notifications_handler(Interface* _interface, Online_users* _online_users)
		{
			interface = _interface;
			online_users = _online_users;
		}
		string notifications = "";
		Response *callback(Request *req)
		{
			Response *res = new Response;
			try
			{
				string id = req->getSessionId();
				for(int i = 0;i < int((online_users->users).size()); i++)
				{
					if((online_users->users)[i].session_id == id)
					{
						interface->log_in((online_users->users)[i].username + " " + (online_users->users)[i].password);
						notifications = interface->notifications();
					}
				}
				res->setHeader("Content-Type", "text/html");
			}
			catch (Exception* exception)
			{
				notifications = "";
				exception->what();
			}
			res->setBody(notifications);
			interface->log_out("");
			return res;
		}
};


class Make_jeek_handler : public RequestHandler {
	private:
		Interface* interface;
		Online_users* online_users;
	public:
		Make_jeek_handler(Interface* _interface, Online_users* _online_users)
		{
			interface = _interface;
			online_users = _online_users;
		}
		Response *callback(Request *req)
		{
			Response *res = new Response;
			try
			{
				string text = "";
				string tag = "";
				string mention = "";
				string id = req->getSessionId();
				for(int i = 0;i < int((online_users->users).size()); i++)
				{
					if((online_users->users)[i].session_id == id)
					{
						interface->log_in((online_users->users)[i].username + " " + (online_users->users)[i].password);
					}
				}
				interface->make_new_jeek();
				text = req->getBodyParam("text");
				interface->add_text(text);
				tag = req->getBodyParam("tag");
				mention = req->getBodyParam("mention");
				stringstream tag_line(tag);
				stringstream mention_line(mention);
				while(tag_line >> tag)
				{
					interface->add_tag(tag);
				}
				while(mention_line >> mention)
				{
					interface->add_mention(mention);
				}
				interface->publish_jeek("");
				res->setHeader("Content-Type", "text/html");
			}
			catch (Exception* exception)
			{
				exception->what();
			}
			res->setBody(readFile("htmlFiles/jeekjeek.html"));
			interface->log_out("");
			return res;
		}
};


class Make_comment_handler : public RequestHandler {
	private:
		Interface* interface;
		Online_users* online_users;
	public:
		Make_comment_handler(Interface* _interface, Online_users* _online_users)
		{
			interface = _interface;
			online_users = _online_users;
		}
		Response *callback(Request *req)
		{
			Response *res = new Response;
			try
			{
				string id = req->getSessionId();
				for(int i = 0;i < int((online_users->users).size()); i++)
				{
					if((online_users->users)[i].session_id == id)
					{
						interface->log_in((online_users->users)[i].username + " " + (online_users->users)[i].password);
					}
				}
				res->setHeader("Content-Type", "text/html");
				string comment_id = "";
				string comment_text = "";
				comment_id = req->getBodyParam("jeek_id");
				comment_text = req->getBodyParam("text");
				comment_id = comment_id.substr(1, comment_id.size());
				string comment_info = comment_id + " " + comment_text;
				interface->comment(comment_info);
			}
			catch (Exception* exception)
			{
				exception->what();
			}
			res->setBody("<script>window.location.href = \"/jeekjeek\" </script>");
			interface->log_out("");
			return res;
		}
};

int main(int argc, char **argv)
{
	Interface* interface = new Interface;
	Online_users* online_users = new Online_users;
	interface->sign_up("zhivar zhivar zhivar ");
	interface->sign_up("negar negar negar ");
	interface->log_in("zhivar zhivar");
	interface->follow("negar");
	interface->make_new_jeek();
	interface->add_text("shit zhivar f;lajd fl;akj df;j dlfk akdf a");
	interface->add_tag("hoora");
	interface->publish_jeek("");
	interface->make_new_jeek();
	interface->add_text("zhivar shit");
	interface->add_tag("hoora");
	interface->publish_jeek("");
	interface->make_new_jeek();
	interface->add_text("zhivar shit");
	interface->publish_jeek("");
	interface->log_out("");
	interface->log_in("negar negar");
	interface->make_new_jeek();
	interface->add_text("shit negar");
	interface->publish_jeek("");
	interface->make_new_jeek();
	interface->add_text("negar shit");
	interface->publish_jeek("");
	interface->make_new_jeek();
	interface->add_text("negar shit");
	interface->publish_jeek("");
	interface->log_out("");
	try {

		Server server(argc > 1 ? atoi(argv[1]) : 5000);

		server.get("/signup_page", new ShowPage("htmlFiles/signup.html"));
		server.post("/signup", new signup_handler(interface, online_users));

		server.get("/home_icon", new ShowImage("htmlFiles/home.png"));
		server.get("/like_icon", new ShowImage("htmlFiles/like.png"));
		server.get("/dislike_icon", new ShowImage("htmlFiles/dislike.png"));
		server.get("/home", new ShowPage("htmlFiles/home.html"));

		server.get("/login_page", new ShowPage("htmlFiles/login.html"));
		server.post("/login", new LoginHandler(interface, online_users));

		server.get("/jeekjeek_page", new ShowPage("htmlFiles/jeekjeek.html"));
		server.post("/jeekjeek", new Jeekjeek_handler(interface, online_users));

		server.post("/getUsername", new Get_username(online_users));
		server.post("/getName", new Get_name(online_users));
		server.post("/logout", new Logout_handler(online_users));

		server.get("/test", new ShowPage("htmlFiles/index.html"));
		server.post("/rejeek", new Rejeek_handler(interface, online_users));
		server.post("/like", new Like_handler(interface, online_users));
		server.post("/get_notifications", new Notifications_handler(interface, online_users));
		server.post("/jeek", new Make_jeek_handler(interface, online_users));
		server.post("/comment", new Make_comment_handler(interface, online_users));

		server.run();

	}
	catch (Server::Exception e)
	{
		cout << e.getMessage() << endl;
	}


}
