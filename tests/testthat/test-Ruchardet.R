context("test Rucharet")

path <- system.file("test-files", package = "Ruchardet")

test_that("test detectEncoding", {
    expect_equal(detectFileEncoding(file.path(path, "big5.txt"), n =-1), "BIG5")
    expect_equal(detectFileEncoding(file.path(path, "gb18030.txt"), n =-1), "GB18030")
    expect_equal(detectFileEncoding(file.path(path, "shift_jis.txt"), n =-1), "SHIFT_JIS")
    expect_equal(detectFileEncoding(file.path(path, "utf8.txt"), n = -1), "UTF-8")
    expect_equal(detectFileEncoding(file.path(path, "euc_kr.txt"), n =-1), "EUC-KR")

    fo <- file(file.path(path, "shift_jis.txt"), 'r')
    expect_equal(detectFileEncoding(fo), "SHIFT_JIS")
    close(fo)
})
