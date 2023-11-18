import os
import glob
import leetcode
import leetcode.auth
import markdownify
from tqdm import tqdm
from tqdm.contrib.concurrent import process_map
import multiprocessing
import time
import argparse


def get_description_from_leetcode(title_slug):
  # Get the next two values from your browser cookies
  # Chrome -> F12 -> Application -> find the `LEETCODE_SESSION`
  # the dependency is markdownify and python-leetcode
  if os.path.exists(".leetcode_session"):
    with open(".leetcode_session", "r", encoding='utf-8') as f:
      leetcode_session = f.read()
  else:
    leetcode_session = os.environ.get("LEETCODE_SESSION", None)
    if leetcode_session is None:
      raise ValueError("LEETCODE_SESSION is not set")
  csrf_token = leetcode.auth.get_csrf_cookie(leetcode_session)

  configuration = leetcode.Configuration()

  configuration.api_key["x-csrftoken"] = csrf_token
  configuration.api_key["csrftoken"] = csrf_token
  configuration.api_key["LEETCODE_SESSION"] = leetcode_session
  configuration.api_key["Referer"] = "https://leetcode.cn"
  configuration.debug = False
  # configuration.verify_ssl = False
  configuration.host = "https://www.leetcode.cn"

  api_instance = leetcode.DefaultApi(leetcode.ApiClient(configuration))

  graphql_request = leetcode.GraphqlQuery(
      query="""
        query getQuestionDetail($titleSlug: String!) {
            question(titleSlug: $titleSlug) {
            questionId
            questionFrontendId
            categoryTitle
            boundTopicId
            title
            titleSlug
            content
            translatedTitle
            translatedContent
            isPaidOnly
            difficulty
            likes
            dislikes
            isLiked
            similarQuestions
            contributors {
                username
                profileUrl
                avatarUrl
                __typename
            }
            langToValidPlayground
            topicTags {
                name
                slug
                translatedName
                __typename
            }
            companyTagStats
            codeSnippets {
                lang
                langSlug
                code
                __typename
            }
            stats
            hints
            solution {
                id
                canSeeDetail
                __typename
            }
            status
            sampleTestCase
            metaData
            judgerAvailable
            judgeType
            mysqlSchemas
            enableRunCode
            envInfo
            book {
                id
                bookName
                pressName
                source
                shortDescription
                fullDescription
                bookImgUrl
                pressImgUrl
                productUrl
                __typename
            }
            isSubscribed
            isDailyQuestion
            dailyRecordStatus
            editorType
            ugcQuestionId
            style
            exampleTestcases
            __typename
            }
        }
        """,
      variables=leetcode.GraphqlQueryGetQuestionDetailVariables(
          title_slug=title_slug
      ),
      operation_name="getQuestionDetail",
  )

  problem = api_instance.graphql_post(body=graphql_request)
  if problem.data.question is None:
    raise ValueError(f"{title_slug} not found")
  # print(problem.data.question.translated_content)
  problem_description = markdownify.markdownify(
      problem.data.question.translated_content,
      strip=["ul", "p"],
      strong_em_symbol=""
  )

  return f"## {problem.data.question.translated_title}\n\n{problem_description}"


def populate_note_for_(src_file_path):
  with open(
      os.path.join(src_file_path, "main.cpp"), "r", encoding='utf-8'
  ) as code:
    lines = code.readlines()
    lines_with_strip = [l.strip() for l in lines]
    comments_head = [
        l for l in lines_with_strip[:14] if l.startswith("* title:")
    ]
    if len(comments_head) != 1:
      raise ValueError("title not found")
    title = comments_head[0][len("* title:"):].strip()
    answer_lines_start = lines_with_strip.index("// @lc code=start")
    answer_lines_end = lines_with_strip.index("// @lc code=end")
    answer_lines = lines[answer_lines_start + 1:answer_lines_end]
    cpp_answer = f"""```cpp\n{"".join(answer_lines)}```\n"""
  problem_description = get_description_from_leetcode(title)
  ans = "-------------\n"
  ans += f"{problem_description}\n\n{cpp_answer}"
  time.sleep(0.5)
  return ans


def header():
  return "# LeetCode 学习笔记\n"


def main():
  parser = argparse.ArgumentParser()
  parser.add_argument(
      "-p",
      "--preview",
      type=str,
      action="store",
      help="preview the note for a specific problem"
  )
  args = parser.parse_args()
  if args.preview:
    print(populate_note_for_(args.preview))
    return
  with open("tools/.noteignore", "r", encoding='utf-8') as f:
    ignore_files = f.readlines()
    ignore_files = [
        l.strip() for l in ignore_files
        if not l.startswith("#") and l.strip() != ""
    ]
  src_dir = set(i.strip('/') for i in set(glob.glob("*/")) - set(ignore_files)
                ) - set(ignore_files)
  note_str = [header()]
  note_str += [
      populate_note_for_(src_file) for src_file in
      tqdm(src_dir, desc="Processing files", unit="file", colour='green')
  ]
  # num_processes = multiprocessing.cpu_count()
  # num_processes += process_map(
  #     populate_note_for_,
  #     src_dir,
  #     max_workers=num_processes,
  #     desc="Processing files",
  #     unit="file",
  #     colour='green'
  # )
  with open("NOTE.md", "w", encoding='utf-8') as f:
    print("\n".join(note_str), file=f)


if __name__ == "__main__":
  main()
