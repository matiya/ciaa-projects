;;; Directory Local Variables
;;; For more information see (info "(emacs) Directory Variables")

;; ((c-mode
;;   ;; (flycheck-clang-include-path . /home/default/Workspace/CIAA/firmware_v2/modules/lpc4337_m4/sapi/inc)
;;   (indent-tabs-mode . t)
;;   (show-trailing-whitespace . t)
;;   (c-basic-offset . 4)
;;   (tab-width . 4)))


;; ((c-mode . ((eval . (setq-local flycheck-clang-include-path
;;                              (list (expand-file-name "headers" (projectile-project-root))
;;                                    (expand-file-name "source/mon" (projectile-project-root))))))
;;       ))

;; ((c-mode . ((indent-tabs-mode .  nil)))
;;  (c++-mode . ((indent-tabs-mode .  nil)))
;;  (nil . ((flycheck-clang-include-path . ("."
;;                                          "../modules/lpc4337_m4/sapi/inc"
;;                                          "../modules/lpc4337_m4/sapi/"
;;                                          "../modules/lpc4337_m4/"
;;                                          "lib/asio/asio/include"
;;                                          "lib/autocheck/include"
;;                                          "lib/cereal/include"
;;                                          "lib/util"
;;                                          "lib/soci/src/core"
;;                                          "lib/soci/src/backends/sqlite3"
;;                                          "lib/xdrpp"
;;                                          "lib/sqlite"
;;                                          "lib/libsodium/src/libsodium"
;;                                          "lib/libmedida/src"
;;                                          ))
;;          (whitespace-style . (face tabs tab-mark trailing lines-tail empty))
;;          (c-file-style . "stroustrup")
;;          (eval . (add-to-list 'auto-mode-alist '("\\.h\\'" . c++-mode)))
;;          (eval . (if (boundp 'c-offsets-alist)
;;                      (add-to-list 'c-offsets-alist '(innamespace . -))))
;; 	 )))
;; ((nil . ((company-clang-arguments . "the value"))))
