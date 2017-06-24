#pragma once

#include <string>
#include <map>

#include <boost/locale.hpp>
#include <boost/algorithm/string.hpp>
#include "tinyxml2/tinyxml2.h"

class Node
{
public:
	using stirng = std::string;
	using ElementPtr = tinyxml2::XMLElement *;
	using Nodes = std::vector<Node>;

public:
	Node() = delete;
	Node(ElementPtr p) : elp_(p) {}

	operator ElementPtr() { return elp_; }
	operator bool() { return (elp_ != nullptr); }
	ElementPtr operator->() { return elp_; }

	Node First(const std::string &name) {
		string lastname;
		ElementPtr p = First_(name, lastname);
		return p;
	}

	Nodes Select(const std::string &name) {
		Nodes nodes;
		string lastname;
		ElementPtr p = First_(name, lastname);

		if (p) {
			do {
				nodes.push_back(p);
				p = p->NextSiblingElement(lastname.c_str());
			} while (p);
		}

		return move(nodes);
	}

	std::string Text(bool fromutf = false) {
		const char *p = nullptr;
		if (elp_) p = elp_->GetText();
		
		string s = p ? p : "";
		if (fromutf) s = FromUTF(s);

		return s;
	}

	std::string Attr(const std::string &n, bool fromutf = false) {
		const char *p = nullptr;
		if (elp_) p = elp_->Attribute(n.c_str());

		string s = p ? p : "";
		if (fromutf) s = FromUTF(s);
		return s;
	}

public:
	static std::string FromUTF(const string &s) {
		return boost::locale::conv::from_utf(s, "euc-kr");
	}

private:
	ElementPtr First_(const std::string &name, std::string &lastname) {
		ElementPtr p = elp_;

		std::vector<string> v;
		boost::split(v, name, boost::is_any_of("/"));

		string sn;
		for (auto en : v) {
			if (!en.empty()) {
				sn = en;
				p = p->FirstChildElement(en.c_str());
				if (!p) break;
			}
		}

		lastname = sn;
		return p;
	}

private:
	ElementPtr elp_;
};