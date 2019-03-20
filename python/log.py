import logging
from logging.handlers import RotatingFileHandler

def init_logger(log):
    """
    init logger
    :param
    :return
    """
    log.setLevel(logging.DEBUG)
    try:
        file_handler = RotatingFileHandler(filename=LOG_PATH, maxBytes=LOG_MAX_BYTES,
                                           backupCount=LOG_MAX_BACKUP)
    except Exception as e:
        print("exception happen, msg is " % e)
        return False

    formatter = logging.Formatter("%(asctime)s [%(process)d:%(thread)d] "
                                  "[%(filename)s:%(lineno)d] %(message)s ", "%Y/%m/%d %H:%M:%S %Z")
    file_handler.setFormatter(formatter)
    log.addHandler(file_handler)
    return True
