#include "read_response.hpp"

#include <nlohmann/json.hpp>
#include <print_logger.hpp>

#include <string_view>

#include "../util/util.hpp"

using json = nlohmann::json;

template <typename String>
String get_if_set(const json& parsed, const char* key)
{
	const auto val = parsed.find(key);
	if (val == parsed.end())
		return "";
	return val->get<String>();
}

std::string read_error(const std::string& response_json)
{
	const auto parsed = json::parse(response_json, nullptr, false); //don't throw on a bad parse

	// a parse fail is fine here because it might just be a plain error string
	// from nginx, for instance
	if (parsed == json::value_t::discarded)
	{
		return "";
	}

	return get_if_set<std::string>(parsed, "error");
}

mastodon_status read_status(const std::string& status_json)
{
	const auto parsed = json::parse(status_json);

	mastodon_status toreturn;

	parsed["id"].get_to(toreturn.id);
	parsed["uri"].get_to(toreturn.url);

	// the mastodon API says these will always be here, but do this to be safe.
	// it also says that spoiler_text won't have html, but I'm not sure how correct that is
	// i suspect it might at least have HTML entities that have to be cleaned up
	toreturn.content_warning = clean_up_html(get_if_set<std::string_view>(parsed, "spoiler_text"));
	toreturn.content = clean_up_html(get_if_set<std::string_view>(parsed, "content"));

	parsed["visibility"].get_to(toreturn.visibility);

	return toreturn;
}

std::string read_upload_id(const std::string& attachment_json)
{
	return json::parse(attachment_json)["id"].get<std::string>();
}
