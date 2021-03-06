// Copyright (c) 2014-2019 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#ifndef TAO_JSON_PEGTL_INTERNAL_AT_HPP
#define TAO_JSON_PEGTL_INTERNAL_AT_HPP

#include "../config.hpp"

#include "skip_control.hpp"
#include "trivial.hpp"

#include "../apply_mode.hpp"
#include "../rewind_mode.hpp"

#include "../analysis/generic.hpp"

namespace TAO_JSON_PEGTL_NAMESPACE::internal
{
   template< typename... Rules >
   struct at;

   template<>
   struct at<>
      : trivial< true >
   {
   };

   template< typename... Rules >
   struct at
   {
      using analyze_t = analysis::generic< analysis::rule_type::opt, Rules... >;

      template< apply_mode,
                rewind_mode,
                template< typename... >
                class Action,
                template< typename... >
                class Control,
                typename Input,
                typename... States >
      [[nodiscard]] static bool match( Input& in, States&&... st )
      {
         const auto m = in.template mark< rewind_mode::required >();
         return ( Control< Rules >::template match< apply_mode::nothing, rewind_mode::active, Action, Control >( in, st... ) && ... );
      }
   };

   template< typename... Rules >
   inline constexpr bool skip_control< at< Rules... > > = true;

}  // namespace TAO_JSON_PEGTL_NAMESPACE::internal

#endif
