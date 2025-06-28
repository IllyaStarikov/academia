refund = c(
    "y",
    "n",
    "n",
    "y",
    "n",
    "n",
    "y",
    "n",
    "n",
    "n"
)
status = c(
    "single",
    "married",
    "single",
    "married",
    "divorced",
    "married",
    "divorced",
    "single",
    "married",
    "single"
)

income_k = c(
    125,
    100,
    70,
    120,
    95,
    60,
    220,
    85,
    75,
    90
)
class = c(
    FALSE,
    FALSE,
    FALSE,
    FALSE,
    TRUE,
    FALSE,
    FALSE,
    TRUE,
    FALSE,
    TRUE
)

tax_info = data.frame(refund, status, income_k, class)
