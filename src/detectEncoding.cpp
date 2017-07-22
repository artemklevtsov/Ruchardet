#include <Rcpp.h>
#include "uchardet.h"

using namespace Rcpp;

//' Detect encoding of input string
//' @param str Character vector.
//' @return Character vector with encoding names. For the unknown encodings return NAs.
//' @references \url{https://www.freedesktop.org/wiki/Software/uchardet/}
//' @export
//' @useDynLib Ruchardet
//' @importFrom Rcpp sourceCpp
// [[Rcpp::export]]
CharacterVector detectEncoding(const CharacterVector& str) {
    R_xlen_t n = str.size();
    CharacterVector res = no_init(n);
    uchardet_t handle = uchardet_new();

    for (R_xlen_t i = 0; i < n; ++i) {
        // Skip detecting for the NA
        if (CharacterVector::is_na(str[i])) {
            res[i] = NA_STRING;
            continue;
        }

        int retval = uchardet_handle_data(handle, str[i], strlen(str[i]));
        uchardet_data_end(handle);
        if (retval == 0)
            res[i] = uchardet_get_charset(handle);
        else
            res[i] = NA_STRING;
        uchardet_reset(handle);
    }

    uchardet_delete(handle);

    return res;
}
