set(hdrs RTC_ImageProcess.h
    PARENT_SCOPE
    imProcessPortSVC_impl.h
    )

install(FILES ${hdrs} DESTINATION ${INC_INSTALL_DIR}/${PROJECT_NAME_LOWER}
    COMPONENT library)

