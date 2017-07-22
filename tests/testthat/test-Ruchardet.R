context("test Rucharet")

test_that("test detectEncoding", {
    expect_equal(detectFileEncoding(file.path("files", "big5.txt"), n =-1), "BIG5")
    expect_equal(detectFileEncoding(file.path("files", "gb18030.txt"), n =-1), "GB18030")
    expect_equal(detectFileEncoding(file.path("files", "shift_jis.txt"), n =-1), "SHIFT_JIS")
    expect_equal(detectFileEncoding(file.path("files", "utf8.txt"), n = -1), "UTF-8")
    expect_equal(detectFileEncoding(file.path("files", "euc_kr.txt"), n =-1), "EUC-KR")

    fo <- file(file.path("files", "shift_jis.txt"), 'r')
    expect_equal(detectFileEncoding(fo), "SHIFT_JIS")
    close(fo)
})
