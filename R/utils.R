#' detect file encoding for inputted file 
#' @param file to read from, or a \code{\link{connection}} which will be opened if necessary, and if so closed at the end of the function call.
#' @param n integer. The (maximal) number of lines to read. Negative values indicate that one should read up to the end of input on the connection.
#' @param default default encoding if fail to expect.
#' @return encoding name
#' @export 
detectFileEncoding <- function(file, n = -1L, default = getOption("encoding")) {
    stopifnot(length(file) == 1L)

    if (is.character(file)) {
        file <- file(file, "rt")
        on.exit(close(file))
    }
    if (!inherits(file, "connection")) 
        stop("'file' must be a character string or connection")

    if (!isOpen(file, "rt")) {
        open(file, "rt")
        on.exit(close(file))
    }

    txt <- paste0(readLines(file, warn = FALSE, n = n), collapse = "")
    enc <- detectEncoding(txt)

    if (enc == ""){
        warning("can't expect encoding, will return 'default' encoding")
        enc <- default
    }

    return(enc)
}
