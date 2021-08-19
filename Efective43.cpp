#include <assert.h>
#include <deque>
#include <iostream>
#include <string>
#include <vector>

using std::begin;
using std::cout;
using std::deque;
using std::end;
using std::endl;
using std::string;
using std::vector;

class CompanyA {
public:
  void sendClearText(const string &msg) { cout << "A send clear text\n"; }
  void sendEncrypted(const string &msg) { cout << "A send encrypted text\n"; }
};

class CompanyB {
public:
  void sendClearText(const string &msg) { cout << "B send clear text\n"; }
  void sendEncrypted(const string &msg) { cout << "B send encrypted text\n"; }
};

class CompanyZ {
public:
  // no sendClearText
  void sendEncrypted(const string &msg) { cout << "Z send encrypted text\n"; }
};

template <typename Company> class MsgSender {
public:
  void sendClear(const string &msg) {
    Company c;
    c.sendClearText(msg);
  }
  void sendSecret(const string &msg) {
    Company c;
    c.sendEncrypted(msg);
  }
};

template <> class MsgSender<CompanyZ> {
public:
  void sendSecret(const string &msg) {
    CompanyZ c;
    c.sendEncrypted(msg);
  }
};

template <typename Company> class LoggingMsgSender : public MsgSender<Company> {
public:
  // using MsgSender<Company>::sendClear;
  // using MsgSender<Company>::sendSecret;
  void sendClearMsg(const string &msg) {
    // do something
    sendClear(msg);
    // MsgSender<Company>::sendClear(msg);
  }
  void sendSecretMsg(const string &msg) {
    // do something
    sendSecret(msg);
    // MsgSender<Company>::sendSecret(msg);
  }
};

int main() {
  string s = "hello";
  LoggingMsgSender<CompanyA> A;
  A.sendClear(s);
  LoggingMsgSender<CompanyB> B;
  B.sendSecret(s);

  //-fpermissive 
  return 0;
}