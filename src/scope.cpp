/*
    File:    scope.cpp
    Author:  Ilya Chikmarev
*/

#include <tuple>
#include "../include/scope.h"

namespace mur128m_scope{
   bool operator < (const Name_occurence& first, const Name_occurence& second)
    {
        return std::tie(first.index_of_definition_,  first.attribute_,  first.kind_)     <
               std::tie(second.index_of_definition_, second.attribute_, second.kind_);
    }

    boost::optional<Name_info> Scope::search(std::size_t name_idx)
    {
        auto it = scope_symbols_.find(name_idx);
        if(it != scope_symbols_.end()){
            return it->second;
        }else{
            return boost::none;
        }
    }

    void Scope::insert(std::size_t name_idx, const Name_occurence& name_occ)
    {
        auto it = scope_symbols_.find(name_idx);
        Name_info ninfo;
        if(it != scope_symbols_.end()){
            ninfo = it->second;
        }
        ninfo.info_.insert(name_occ);
        scope_symbols_[name_idx] = ninfo;
    }

    void Symbol_table::add_scope()
    {
        table_.push_front(std::make_shared<Scope>());
        num_of_scopes_++;
    }

    void Symbol_table::delete_scope()
    {
        if(!num_of_scopes_){
            return;
        }
        table_.pop_front();
        num_of_scopes_--;
    }

    void Symbol_table::insert(std::size_t name_idx, const Name_occurence& name_occ)
    {
        if(!num_of_scopes_){
            add_scope();
        }
        auto current = table_.front();
        current->insert(name_idx, name_occ);
    }

    Search_result Symbol_table::search(std::size_t name_idx)
    {
        Search_result result;
        if(!num_of_scopes_){
            return Name_is_not_found{};
        }
        std::size_t current_scope_number = 0;
        for(const auto& scp : table_){
            auto current_result = scp->search(name_idx);
            if(current_result){
                auto info = *current_result;
                if(num_of_scopes_ == current_scope_number){
                    return Name_in_global_scope{info};
                }else{
                    return Name_in_local_scope{info};
                }
            }else{
                current_scope_number++;
            }
        }
        return Name_is_not_found{};
    }
};
