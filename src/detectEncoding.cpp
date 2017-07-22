#include <Rcpp.h>
#include <string.h>
#include "uchardet.h"

using namespace Rcpp;

//' Detect encoding of input string
//' @param str Character vector.
//' @return Character vector with encoding names.
//' @references \url{https://www.freedesktop.org/wiki/Software/uchardet/}
//' @export
//' @useDynLib Ruchardet
//' @importFrom Rcpp sourceCpp
// [[Rcpp::export]]
CharacterVector detectEncoding(const CharacterVector& str) {
    R_xlen_t n = str.size();
    
    uchardet_t handle = uchardet_new();
    
    CharacterVector res = no_init(n);
    
    for (R_xlen_t i = 0; i < n; ++i) {
        uchardet_handle_data(handle, str[i], strlen(str[i]));
        uchardet_data_end(handle);
        res[i]  = uchardet_get_charset(handle);
        uchardet_reset(handle);
    }
    
    uchardet_delete(handle);
    
    return res;
}
