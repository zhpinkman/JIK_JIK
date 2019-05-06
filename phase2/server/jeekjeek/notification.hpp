#ifndef NOTIFICATION
#define NOTIFICATION NOTIFICATION

#include <string>
using namespace std;

class Jeek;
class User;

class Notification
{
public:
  void make_like_notification(User* user, string id, bool like);
  void make_comment_notification(User* user, string jeek_id);
  void make_reply_notification(User* user, string comment_id);
  void make_jeek_notification(User* user, string jeek_id);
  void make_mention_notification(User* user, Jeek* new_jeek, string jeek_id);
  void make_rejeek_notification(User* user, string jeek_id);
  string show();
  void add_to_notifications(string notification);

protected:
  vector<string> notifications;
};

#endif
