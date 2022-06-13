pub fn enable_debug() -> bool {
    cfg!(feature = "debug")
}

pub fn supports_cmdline() -> bool {
    cfg!(feature = "cmdline")
}

pub fn supports_ntoa() -> bool {
    cfg!(feature = "ntoa")
}
