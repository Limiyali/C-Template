#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <list>
using namespace std;
using MessageBus = map<int, int>;

class AccessManagerBase {
public:
	explicit AccessManagerBase(MessageBus &msg_bus)
		: msg_bus_(msg_bus) {}

protected:
	MessageBus &msg_bus_;
};  // end AccessManagerBase

// ReadAccessManager
template <int ... Messages>
class ReadAccessManager;

template <>
class ReadAccessManager<> : public AccessManagerBase {
public:
	explicit ReadAccessManager(MessageBus &msg_bus)
		: AccessManagerBase(msg_bus) {}
};

template <int Last>
class ReadAccessManager<Last> : public ReadAccessManager<> {
protected:
	int _GetMessage(const int &type) {
		return msg_bus_[type];
	}

	// template <typename Inner>
	// std::shared_ptr<Inner> GetMessageTraits(Optional<Inner> *) {
	//   return std::dynamic_pointer_cast<typename Optional<Inner>::type>(
	//       this->_GetMessage(Optional<Inner>::type::sGetName()));
	// }

public:
  explicit ReadAccessManager(MessageBus &msg_bus)
      : ReadAccessManager<>(msg_bus) {
    cout << Last << " ";
  }

  int GetMessageTraits(int id) { return _GetMessage(id); }

  auto GetMessage(char) { return _GetMessage(Last); }
};

template <int First, int... Others>
class ReadAccessManager<First, Others...> :
	public ReadAccessManager<Others...> {
public:
	explicit ReadAccessManager(MessageBus &msg_bus)
		: ReadAccessManager<Others...>(msg_bus) {
		cout << First << " ";
	}
  
	int GetMessage(int) {
    cout<<" get "<<First<<endl;
		return this->GetMessageTraits(First);
	}

	using ReadAccessManager<Others...>::GetMessage;
};  // end ReadAccessManager

template <typename AccessManager, typename Msg>
auto GetMessage(AccessManager &access_mgr, Msg *msg)->decltype(msg->begin()) {
	cout << "1\n";
  return msg->begin();
}

template <typename AccessManager, typename Msg>
auto GetMessage(AccessManager &access_mgr, Msg *)->decltype((static_cast<AccessManager *>(nullptr))->begin()) {
	cout << "2\n";
  vector<int>a;
  return a.begin();
}

template <typename T> typename enable_if<std::is_same<T, char>::value>::type f() {
  // typename enable_if<std::is_same<T, T>::value>::type a;
  // cout << typeid(a).name() << endl;
}

int main() {
	// MessageBus messages;
	// for (int i = 0; i < 10; i++) {
	// 	int key = i + 100;
	// 	messages[key] = i;
	// }
	// for (auto it : messages)
	// 	cout << it.first << " " << it.second << " ";
	// cout << endl;
	// ReadAccessManager<100, 101, 102, 105> read(messages);
	// cout << endl;
	// cout << read.GetMessage(3) << endl;
  vector<int>* b = (static_cast<vector<int> *>(nullptr));
  cout << b->begin();
}