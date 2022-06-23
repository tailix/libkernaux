pub fn with_cmdline() -> bool {
    cfg!(feature = "cmdline")
}

pub fn with_ntoa() -> bool {
    cfg!(feature = "ntoa")
}
