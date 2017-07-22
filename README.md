
<!-- README.md is generated from README.Rmd. Please edit that file -->
Ruchardet
=========

An R bindings of the [uchardet](https://www.freedesktop.org/wiki/Software/uchardet/) library.

Installation
------------

To install the package from the CRAN run the following command:

``` r
install.packages("Ruchardet", repos = "https://cloud.r-project.org/")
```

To install the development version from git repository the `install_git()` function from `devtools` package can be used:

``` r
devtools::install_github('Ruchardet', 'haven-jeon')
```

Usage
-----

``` r
library(Ruchardet, quietly = TRUE)

nm <- '안녕하세요! 고감자입니다'
benc <- detectEncoding(nm)
benc
#> [1] "UTF-8"
nme <- iconv(nm, benc, "CP949")
detectEncoding(c(nm, nme))
#> [1] "UTF-8"  "EUC-KR"

# Detection of unknown file encoding
tmp <- tempfile()
writeLines(nme, tmp)
detectFileEncoding(tmp)
#> [1] "EUC-KR"

# URL encoding detection 
detectFileEncoding('http://www.ppomppu.co.kr/')
#> [1] "EUC-KR"
detectFileEncoding('http://freesearch.pe.kr')
#> [1] "UTF-8"
```

Bug reports
-----------

Use the following command to go to the page for bug report submissions:

``` r
bug.report(package = "benchr")
```
