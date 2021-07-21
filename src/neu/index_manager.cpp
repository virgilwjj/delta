#include "neu/index_manager.h"

#include "neu/core.h"

#include <sstream>

namespace neu
{
    auto
    init_basic_inverted_index(const std::string &basic_str)
    {
        index_manager::basic_inverted_index_type basic_inverted_index{};
        index_manager::offset_type begin{0}, end{0};
        bool is_find_begin{false};
        for (index_manager::offset_type i{0}; i < basic_str.size(); ++i)
        {
            const auto &ch{basic_str[i]};
            if (ch != ' ')
            {
                if (!is_find_begin)
                {
                    is_find_begin = true;
                    begin = i;
                }
                end = i;
            }
            if (ch == ' ' || i == basic_str.size() - 1 && is_find_begin)
            {
                is_find_begin = false;
                auto token{basic_str.substr(begin, end - begin + 1)};
                auto &offset_set{basic_inverted_index[token]};
                offset_set.emplace(begin);
            }
        }
        return basic_inverted_index;
    }

    index_manager::index_manager(const std::string &basic_str)
        : basic_str_{basic_str},
        basic_inverted_index_{init_basic_inverted_index(basic_str)}
    {
    }

    void
    index_manager::push_token_by_id_and_delta(const doc_id_type doc_id, const std::vector<node> &delta)
    {
        for (std::vector<node>::size_type index{0}; index < delta.size(); ++index)
        {
            //auto [merged_str, left_index, _] = partial_merge_str(basic_str_, delta, index);
            std::string token{};
            offset_type offset{};
            auto &doc_id_umap{inverted_index_[token]};
            auto &offset_set{doc_id_umap[doc_id]};
            offset_set.emplace(offset);
        }
    }

    std::vector<std::unordered_set<index_manager::offset_type>>
    index_manager::regex_query(const std::string &regex_str)
    {
        return {};
    }
};