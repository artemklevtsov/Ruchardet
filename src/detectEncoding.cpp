#include <Rcpp.h>
#include "uchardet.h"

using namespace Rcpp;

//' Detect encoding of input string
//' @param str Character vector.
//' @return Character vector with encoding names. For the unknown encodings return NAs.
//' @references \url{https://www.freedesktop.org/wiki/Software/uchardet/}
//' @export
//' @useDynLib Ruchardet, .registration = TRUE
//' @importFrom Rcpp sourceCpp
// [[Rcpp::export]]
CharacterVector detectEncoding(const CharacterVector& str) {
    R_xlen_t n = str.size();

    // Allocate vector without initialization
    CharacterVector res = no_init(n);

    // Create handler
    uchardet_t handle = uchardet_new();

    for (R_xlen_t i = 0; i < n; ++i) {
        // Skip detecting for NAs
        if (CharacterVector::is_na(str[i])) {
            res[i] = NA_STRING;
            continue;
        }

        // Detect encoding
        int retval = uchardet_handle_data(handle, str[i], strlen(str[i]));
        uchardet_data_end(handle);

        // Get encoding
        if (retval == 0)
            res[i] = uchardet_get_charset(handle);
        else
            res[i] = NA_STRING;

        // Reset handler
        uchardet_reset(handle);
    }

    // Remove handler
    uchardet_delete(handle);

    // Keep names if exists
    if (str.hasAttribute("names"))
        res.names() = str.names();

    return res;
}
