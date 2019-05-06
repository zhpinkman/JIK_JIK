#include "user.hpp"
#include "exception.hpp"

void Notification::add_to_notifications(string notification)
{
  notifications.push_back(notification);
}
void Notification::show()
{
  int num_of_notifications = notifications.size();
  if(num_of_notifications == 0)
    throw (new No_notifications);
  for(int i = num_of_notifications - 1 ;i >= 0 ; i--)
  {
    cout << notifications[0] << endl;
    notifications.erase(notifications.begin());
  }
}
void Notification::make_like_notification(User* user, string id, bool like)
{
  string notification = "";
  string like_part = "";
  if(like)
    like_part = " liked ";
  else
    like_part = " disliked ";
  notification = user->get_username() + like_part + id;
  user->send_notification(notification);
}

void Notification::make_reply_notification(User* user, string comment_id)
{
  string notification = "";
  notification = user->get_username() + " replied " + comment_id;
  user->send_notification(notification);
}

void Notification::make_rejeek_notification(User* user, string jeek_id)
{
  string notification = "";
  notification = user->get_username() + " rejeeked " + jeek_id;
  user->send_notification(notification);
}

void Notification::make_mention_notification(User* user, Jeek* new_jeek, string jeek_id)
{
  string notification = "";
  notification = user->get_username() + " mentioned you in " + jeek_id;
  new_jeek->send_mention_notification(notification);
}

void Notification::make_jeek_notification(User* user, string jeek_id)
{
  string notification = "";
  notification = user->get_username() + " jeeked " + jeek_id;
  user->send_notification(notification);
}

void Notification::make_comment_notification(User* user, string jeek_id)
{
  string notification = "";
  notification = user->get_username() + " commented on " + jeek_id;
  user->send_notification(notification);
}
