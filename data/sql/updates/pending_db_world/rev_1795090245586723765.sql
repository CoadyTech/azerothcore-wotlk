--
-- Changes another account's two-factor secret: admin only, like the other account set commands
UPDATE `command` SET `security` = 3 WHERE `name` = 'account set 2fa';
