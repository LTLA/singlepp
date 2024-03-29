# Generated by using Rcpp::compileAttributes() -> do not edit by hand
# Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#' @export
integrate_singlepp <- function(mat, results, refs, labels, markers, quantile = 0.8) {
    .Call('_singlepp_tests_integrate_singlepp', PACKAGE = 'singlepp.tests', mat, results, refs, labels, markers, quantile)
}

#' @useDynLib singlepp.tests
#' @importFrom Rcpp sourceCpp
#' @export
run_singlepp <- function(mat, ref, labels, markers, quantile = 0.8, fine_tune = TRUE, tune_thresh = 0.05, top = 20L) {
    .Call('_singlepp_tests_run_singlepp', PACKAGE = 'singlepp.tests', mat, ref, labels, markers, quantile, fine_tune, tune_thresh, top)
}

