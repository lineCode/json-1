// Copyright (c) 2018-2019 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAO_JSON_UBJSON_EVENTS_PARSE_FILE_HPP
#define TAO_JSON_UBJSON_EVENTS_PARSE_FILE_HPP

#include <utility>

#include "../../external/pegtl/file_input.hpp"
#include "../../external/pegtl/parse.hpp"

#include "../internal/grammar.hpp"

namespace tao
{
   namespace json
   {
      namespace ubjson
      {
         namespace events
         {
            // Events producer to parse a file containing a UBJSON string representation.

            template< typename T, typename Consumer >
            void parse_file( Consumer& consumer, T&& filename )
            {
               pegtl::file_input< pegtl::tracking_mode::lazy > in( std::forward< T >( filename ) );
               pegtl::parse< internal::grammar >( in, consumer );
            }

         }  // namespace events

      }  // namespace ubjson

   }  // namespace json

}  // namespace tao

#endif
