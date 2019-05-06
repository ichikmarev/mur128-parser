/*
    File:    scope.h
    Author:  Ilya Chikmarev
*/

#ifndef SCOPE_H
#define SCOPE_H
#   include <cstdint>
#   include <cstddef>
#   include <set>
#   include <map>
#   include <boost/optional.hpp>
#   include <boost/variant.hpp>
#   include <forward_list>
#   include <memory>
namespace mur128m_scope{
    enum class Name_kind : std::uint16_t{
        Variable,     Function,     Type,
        Enum,         Struct,       Enum_elem,
        Struct_field, Cycle_label
    };

    struct Name_occurence{
        std::size_t index_of_definition_ = 0;
        std::size_t attribute_           = 0;
        Name_kind   kind_                = Name_kind::Variable;
    };

    bool operator < (const Name_occurence& first, const Name_occurence& second);

    struct Name_info{
        std::set<Name_occurence> info_;
    };

    class Scope{
    public:
        Scope()                              = default;
        Scope(const Scope& src)              = default;
        virtual ~Scope()                     = default;
        Scope& operator = (const Scope& rhs) = default;

        boost::optional<Name_info> search(std::size_t name_idx);
        void insert(std::size_t name_idx, const Name_occurence& name_occ);
    private:
        std::map<std::size_t, Name_info> scope_symbols_;
    };

    struct Name_in_global_scope{
        Name_info info_;
    };

    struct Name_in_local_scope{
        Name_info info_;
    };

    struct Name_is_not_found{};

    using Search_result = boost::variant<Name_in_global_scope,
                                         Name_in_local_scope,
                                         Name_is_not_found>;

    class Symbol_table{
    public:
        Symbol_table()                                     = default;
        Symbol_table(const Symbol_table& src)              = default;
        virtual ~Symbol_table()                            = default;
        Symbol_table& operator = (const Symbol_table& rhs) = default;

        void add_scope();
        void delete_scope();

        void insert(std::size_t name_idx, const Name_occurence& name_occ);

        Search_result search(std::size_t name_idx);
    private:
        std::forward_list<std::shared_ptr<Scope>> table_;
        std::size_t                               num_of_scopes_ = 0;
    };
};
#endif
